#include "Recorder.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Recorder::Recorder(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->utl_chrono = new sys::timer::Chrono();
  this->vk_render = new vk::draw::Renderpass(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_command = new vk::commandbuffer::Command_buffer(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_graphical = new vk::draw::Graphical(vk_struct);

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::record_rendering(vk::structure::Render& render){
  vk_struct->core.profiler.vec_command_buffer.clear();
  //---------------------------

  //Acquiere image
  render.semaphore = vk_semaphore->query_free_semaphore();
  bool sucess = vk_graphical->acquire_next_image(render);
  if(!sucess) return;

  //Rendering
  for(auto& renderpass : vk_struct->core.drawer.vec_renderpass){
    render.renderpass = renderpass;

    //Render pass
    this->prepare_render(render);
    vk_render->run_renderpass(render);
    this->prepare_command(render);
  }

  vk_graphical->copy_to_swapchain(render);

  //---------------------------
}

//Subfunction
void Recorder::prepare_render(vk::structure::Render& render){
  //---------------------------

  render.ts = utl_chrono->start_t();
  render.command_buffer = vk_command->query_free_command_buffer(vk_struct->core.device.queue.graphics);
  render.command_buffer->name = render.renderpass->name;

  //---------------------------
}
void Recorder::prepare_command(vk::structure::Render& render){
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
