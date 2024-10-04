#include "Renderer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Renderer::Renderer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_surface = new vk::presentation::Surface(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_recorder = new vk::draw::Recorder(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_submission = new vk::draw::Submission(vk_struct);

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::make_rendering(){
  vk::structure::Render render;
  //---------------------------

  //Rendering
  vk_recorder->record_rendering(render);

  //Submission
  vk_submission->submit_rendering(render);
  vk_submission->submit_presentation(render);
  vk_swapchain->next_frame_ID();

  //End rendering
  vk_semaphore->reset_pool();
  vk_imgui->glfw_new_frame();

  //---------------------------
}

//Subfunction

}
