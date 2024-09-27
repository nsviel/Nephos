#include "Renderer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Renderer::Renderer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_command = new vk::command::Command(vk_struct);
  this->vk_allocator = new vk::command::Allocator(vk_struct);

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::run_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::pool::structure::Command_buffer* pool = vk_allocator->query_free_pool(&vk_struct->core.device.queue.graphics);
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_command->query_free_command_buffer(pool);
  renderpass->command_buffer = command_buffer;
  command_buffer->name = renderpass->name;

  this->start_renderpass(renderpass);
  this->draw_subpass(renderpass);
  this->stop_renderpass(renderpass);

  vk_command->end_command_buffer(*command_buffer);

  //---------------------------
}

//Subfunction
void Renderer::start_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  VkFramebuffer framebuffer = renderpass->framebuffer.handle;

  vk_command->start_command_buffer_primary(*renderpass->command_buffer);

  std::array<VkClearValue, 2> clear_value{};
  clear_value[0].color = {{
    vk_struct->interface.param.background_color.x,
    vk_struct->interface.param.background_color.y,
    vk_struct->interface.param.background_color.z,
    vk_struct->interface.param.background_color.w}};
  clear_value[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderpass_info.renderPass = renderpass->handle;
  renderpass_info.framebuffer = framebuffer;
  renderpass_info.renderArea.offset = {0, 0};
  renderpass_info.renderArea.extent = vk_struct->window.extent;
  renderpass_info.clearValueCount = static_cast<uint32_t>(clear_value.size());
  renderpass_info.pClearValues = clear_value.data();

  bool with_secondary_cb = false;
  VkSubpassContents content;
  if(with_secondary_cb){
    content = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;
  }else{
    content = VK_SUBPASS_CONTENTS_INLINE;
  }

  vkCmdBeginRenderPass(renderpass->command_buffer->handle, &renderpass_info, content);

  //---------------------------
}
void Renderer::stop_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vkCmdEndRenderPass(renderpass->command_buffer->handle);

  //---------------------------
}
void Renderer::draw_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  for (size_t i = 0; i < renderpass->vec_subpass.size(); ++i) {
    auto& subpass = renderpass->vec_subpass[i];

    //Draw operation
    subpass->command_buffer = renderpass->command_buffer;
    subpass->draw_task(subpass);

    //Next subpass
    if (i < renderpass->vec_subpass.size() - 1) {
      vkCmdNextSubpass(renderpass->command_buffer->handle, VK_SUBPASS_CONTENTS_INLINE);
    }
  }

  //---------------------------
}


}