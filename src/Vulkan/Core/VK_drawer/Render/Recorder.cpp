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
  this->vk_renderpass = new vk::draw::Renderpass(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);
  this->vk_command = new vk::commandbuffer::Command_buffer(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_graphical = new vk::draw::Graphical(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->utl_chrono = new sys::timer::Chrono();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::record_rendering(vk::structure::Render& render){
  vk_struct->core.profiler.vec_command_buffer.clear();
  //---------------------------

  vk_graphical->acquire_swapchain_image(render);
  this->record_all_renderpass(render);
  vk_graphical->copy_to_swapchain(render);

  //---------------------------
}

//Subfunction
void Recorder::record_all_renderpass(vk::structure::Render& render){
  //---------------------------

  for(auto& renderpass : vk_struct->core.drawer.vec_renderpass){
    render.renderpass = renderpass;
    vk_renderpass->run_renderpass(render);
  }

  //---------------------------
}


}
