#include "Renderpass.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_command = new vk::commandbuffer::Command_buffer(vk_struct);
  this->vk_allocator = new vk::commandbuffer::Allocator(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_viewport = new vk::presentation::Viewport(vk_struct);
  this->utl_chrono = new sys::timer::Chrono();

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::record_all_renderpass(std::shared_ptr<vk::structure::Batch> batch){
  //---------------------------

  for(auto& renderpass : vk_struct->core.drawer.vec_renderpass){
    std::shared_ptr<vk::structure::Render> render = std::make_shared<vk::structure::Render>();
    render->renderpass = renderpass;
    render->semaphore = batch->semaphore;
    render->framebuffer = std::make_shared<vk::structure::Framebuffer>(renderpass->framebuffer.window);
    render->viewport = std::make_shared<vk::structure::Viewport>(vk_struct->core.viewport);

    this->record_renderpass(render);

    batch->vec_command.push_back(std::move(render->command));
    batch->semaphore = render->semaphore;
    batch->vec_render.push_back(render);
  }

  //---------------------------
}
void Renderpass::record_renderpass(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  this->prepare_renderpass(render);
  this->start_renderpass(render);
  this->draw_subpass(render);
  this->stop_renderpass(render);
  this->prepare_command(render);

  //---------------------------
}

//Subfunction
void Renderpass::prepare_renderpass(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  render->ts = utl_chrono->start_t();
  render->command_buffer = vk_command->query_graphics_command_buffer(render->renderpass->name);

  //---------------------------
}
void Renderpass::start_renderpass(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vk_command->start_command_buffer_primary(*render->command_buffer);
  this->cmd_viewport(render);

  std::array<VkClearValue, 2> clear_value{};
  clear_value[0].color = {{
    vk_struct->interface.param.background_color.x,
    vk_struct->interface.param.background_color.y,
    vk_struct->interface.param.background_color.z,
    vk_struct->interface.param.background_color.w}};
  clear_value[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderpass_info.renderPass = render->renderpass->handle;
  renderpass_info.framebuffer = render->framebuffer->handle;
  renderpass_info.renderArea.offset = {0, 0};
  renderpass_info.renderArea.extent.width = render->framebuffer->width;
  renderpass_info.renderArea.extent.height = render->framebuffer->height;
  renderpass_info.clearValueCount = static_cast<uint32_t>(clear_value.size());
  renderpass_info.pClearValues = clear_value.data();

  bool with_secondary_cb = false;
  VkSubpassContents content;
  if(with_secondary_cb){
    content = VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS;
  }else{
    content = VK_SUBPASS_CONTENTS_INLINE;
  }

  vkCmdBeginRenderPass(render->command_buffer->handle, &renderpass_info, content);

  //---------------------------
}
void Renderpass::draw_subpass(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  render->subset_ID = 0;
  for(auto& subpass : render->renderpass->vec_subpass){
    render->subpass = subpass;
    render->subpass->draw_task(render);
    this->cmd_next_subset(render);
  }

  //---------------------------
}
void Renderpass::stop_renderpass(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  vkCmdEndRenderPass(render->command_buffer->handle);
  vk_command->end_command_buffer(*render->command_buffer);

  //---------------------------
}
void Renderpass::cmd_next_subset(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  if(render->subset_ID < render->renderpass->vec_subpass.size() - 1){
    vkCmdNextSubpass(render->command_buffer->handle, VK_SUBPASS_CONTENTS_INLINE);
    render->subset_ID++;
  }

  //---------------------------
}
void Renderpass::prepare_command(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  //Create command
  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->command_buffer = render->command_buffer;

  //Semaphore
  if(render->semaphore){
    command->semaphore_wait = render->semaphore->handle;
    render->semaphore = vk_semaphore->query_free_semaphore();
    command->semaphore_done = render->semaphore->handle;
  }

  //Store command
  render->command = std::move(command);
  render->renderpass->duration = utl_chrono->stop_ms(render->ts);

  //---------------------------
}
void Renderpass::cmd_viewport(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  //Viewport
  vkCmdSetViewport(render->command_buffer->handle, 0, 1, &render->viewport->handle);

  //Scissor
  vkCmdSetScissor(render->command_buffer->handle, 0, 1, &render->viewport->scissor);

  //---------------------------
}

}
