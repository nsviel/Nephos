#include "Renderpass.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_command = new vk::commandbuffer::Command_buffer(vk_struct);
  this->vk_allocator = new vk::commandbuffer::Allocator(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->utl_chrono = new sys::timer::Chrono();

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::record_all_renderpass(vk::structure::Render& render){
  vk_struct->core.profiler.vec_command_buffer.clear();
  //---------------------------

  for(auto& renderpass : vk_struct->core.drawer.vec_renderpass){
    render.renderpass = renderpass;
    this->record_renderpass(render);
  }

  //---------------------------
}
void Renderpass::record_renderpass(vk::structure::Render& render){
  //---------------------------

  this->prepare_renderpass(render);
  this->start_renderpass(render);
  this->draw_subpass(render);
  this->stop_renderpass(render);
  this->prepare_command(render);

  //---------------------------
}

//Subfunction
void Renderpass::prepare_renderpass(vk::structure::Render& render){
  //---------------------------

  render.ts = utl_chrono->start_t();
  render.command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  render.command_buffer->name = render.renderpass->name;

  //---------------------------
}
void Renderpass::start_renderpass(vk::structure::Render& render){
  //---------------------------

  VkFramebuffer framebuffer = render.renderpass->framebuffer.handle;

  vk_command->start_command_buffer_primary(*render.command_buffer);

  std::array<VkClearValue, 2> clear_value{};
  clear_value[0].color = {{
    vk_struct->interface.param.background_color.x,
    vk_struct->interface.param.background_color.y,
    vk_struct->interface.param.background_color.z,
    vk_struct->interface.param.background_color.w}};
  clear_value[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderpass_info.renderPass = render.renderpass->handle;
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

  vkCmdBeginRenderPass(render.command_buffer->handle, &renderpass_info, content);

  //---------------------------
}
void Renderpass::draw_subpass(vk::structure::Render& render){
  //---------------------------

  render.subset_ID = 0;
  for(auto& subpass : render.renderpass->vec_subpass){
    render.subpass = subpass;
    render.subpass->draw_task(render);
    this->cmd_next_subset(render);
  }

  //---------------------------
}
void Renderpass::stop_renderpass(vk::structure::Render& render){
  //---------------------------

  vkCmdEndRenderPass(render.command_buffer->handle);
  vk_command->end_command_buffer(*render.command_buffer);

  //---------------------------
}
void Renderpass::cmd_next_subset(vk::structure::Render& render){
  //---------------------------

  if (render.subset_ID < render.renderpass->vec_subpass.size() - 1) {
    vkCmdNextSubpass(render.command_buffer->handle, VK_SUBPASS_CONTENTS_INLINE);
    render.subset_ID++;
  }

  //---------------------------
}
void Renderpass::prepare_command(vk::structure::Render& render){
  //---------------------------

  //Create command
  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  command->command_buffer = render.command_buffer;

  //Semaphore
  command->semaphore_wait = render.semaphore->handle;
  render.semaphore = vk_semaphore->query_free_semaphore();
  command->semaphore_done = render.semaphore->handle;

  //Store command
  render.vec_command.push_back(std::move(command));
  render.renderpass->duration = utl_chrono->stop_ms(render.ts);

  //---------------------------
}

}
