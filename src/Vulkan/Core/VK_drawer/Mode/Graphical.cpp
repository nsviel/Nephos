#include "Graphical.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Graphical::Graphical(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->utl_chrono = new sys::timer::Chrono();
  this->vk_render = new vk::draw::Renderer(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_command = new vk::commandbuffer::Command_buffer(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);

  //---------------------------
}
Graphical::~Graphical(){}

//Main function
void Graphical::record_rendering(vk::structure::Render& render){
  //---------------------------

  //Acquiere image
  render.semaphore = vk_semaphore->query_free_semaphore();
  bool sucess = this->acquire_next_image(render);
  if(!sucess) return;

  //Rendering
  this->record_renderpass(render);
  this->copy_to_swapchain(render);

  //---------------------------
}

bool Graphical::acquire_next_image(vk::structure::Render& render){
  vk::structure::Swapchain& swapchain = vk_struct->core.swapchain;
  //---------------------------

  //Acquiring an image from the swap chain
  if(vk_window->is_window_resized()){
    vk_swapchain->recreate_swapchain();
    return false;
  }
  VkResult result = vkAcquireNextImageKHR(vk_struct->core.device.handle, swapchain.handle, UINT64_MAX, render.semaphore->handle, VK_NULL_HANDLE, &swapchain.current_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapchain();
    return false;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image");
    return false;
  }

  //---------------------------
  return true;
}
void Graphical::record_renderpass(vk::structure::Render& render){
  vk_struct->core.profiler.vec_command_buffer.clear();
  //---------------------------

  for(auto& renderpass : vk_struct->core.drawer.vec_renderpass){
    render.renderpass = renderpass;

    //Render pass
    this->prepare_render(render);
    vk_render->run_renderpass(render);
    this->prepare_command(render);
  }

  //---------------------------
}
void Graphical::copy_to_swapchain(vk::structure::Render& render){
  //---------------------------

  //Copy renderpass to swapchain image
  vk::structure::Renderpass& renderpass = *vk_struct->graphics.render.renderpass.presentation;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = vk_transfer->copy_gpu_image_to_gpu_image(render.renderpass->framebuffer.color, vk_struct->core.swapchain.vec_frame[vk_struct->core.swapchain.current_ID]->color);

  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->semaphore_wait = render.semaphore->handle;
  command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  command->command_buffer = command_buffer;
  render.semaphore = vk_semaphore->query_free_semaphore();
  command->semaphore_done = render.semaphore->handle;
  render.vec_command.push_back(std::move(command));

  //---------------------------
}

//Subfunction
void Graphical::prepare_render(vk::structure::Render& render){
  //---------------------------

  render.ts = utl_chrono->start_t();
  render.command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  render.command_buffer->name = render.renderpass->name;

  //---------------------------
}
void Graphical::prepare_command(vk::structure::Render& render){
  //---------------------------

  std::unique_ptr<vk::structure::Command> command = std::make_unique<vk::structure::Command>();
  command->semaphore_wait = render.semaphore->handle;
  command->wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  command->command_buffer = render.command_buffer;
  render.semaphore = vk_semaphore->query_free_semaphore();
  command->semaphore_done = render.semaphore->handle;
  render.vec_command.push_back(std::move(command));

  render.renderpass->duration = utl_chrono->stop_ms(render.ts);

  //---------------------------
}

}
