#include "Renderer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Renderer::Renderer(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_command_buffer = new vk::command::Command_buffer(struct_vulkan);

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::run_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::pool::Command_buffer* pool = &struct_vulkan->device.queue.graphics.command_buffer;
  vk::structure::Command_buffer* command_buffer = vk_command_buffer->query_free_command_buffer(pool);
  renderpass->command_buffer = command_buffer;
  command_buffer->name = renderpass->name;

  this->start_renderpass(renderpass);
  this->draw_subpass(renderpass);
  this->stop_renderpass(renderpass);

  vk_command_buffer->end_command_buffer(command_buffer);

  //---------------------------
}

//Subfunction
void Renderer::start_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  VkFramebuffer fbo;
  if(renderpass->target == "graphics" || renderpass->target == "transfert"){
    fbo = renderpass->framebuffer->fbo;
  }
  else if(renderpass->target == "presentation"){
    fbo = struct_vulkan->swapchain.get_frame_presentation()->fbo;
  }
  else{
    cout<<"[error] Renderpass target not recognized ["<<renderpass->target<<"]"<<endl;
  }

  vk_command_buffer->start_command_buffer_primary(renderpass->command_buffer);

  std::array<VkClearValue, 2> clear_value{};
  clear_value[0].color = {{
    struct_vulkan->param.background_color.x,
    struct_vulkan->param.background_color.y,
    struct_vulkan->param.background_color.z,
    struct_vulkan->param.background_color.w}};
  clear_value[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderpass_info.renderPass = renderpass->renderpass;
  renderpass_info.framebuffer = fbo;
  renderpass_info.renderArea.offset = {0, 0};
  renderpass_info.renderArea.extent = struct_vulkan->window.extent;
  renderpass_info.clearValueCount = static_cast<uint32_t>(clear_value.size());
  renderpass_info.pClearValues = clear_value.data();

  bool with_secondary_cb = false;
  VkSubpassContents content;
  if(with_secondary_cb){
    content = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;
  }else{
    content = VK_SUBPASS_CONTENTS_INLINE;
  }

  vkCmdBeginRenderPass(renderpass->command_buffer->command, &renderpass_info, content);

  //---------------------------
}
void Renderer::stop_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vkCmdEndRenderPass(renderpass->command_buffer->command);

  //---------------------------
}
void Renderer::draw_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  for(int j=0; j<renderpass->vec_subpass.size(); j++){
    vk::structure::Subpass* subpass = renderpass->vec_subpass[j];
    subpass->command_buffer = renderpass->command_buffer;
    subpass->draw_task(subpass);
  }

  //---------------------------
}


}
