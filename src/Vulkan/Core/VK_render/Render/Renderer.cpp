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
  this->vk_renderpass = new vk::draw::Renderpass(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_submission = new vk::draw::Submission(vk_struct);
  this->vk_graphical = new vk::draw::Graphical(vk_struct);
  this->vk_pipeline = new vk::compute::Pipeline(vk_struct);

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::loop(){
  //---------------------------

  this->make_rendering();

  //---------------------------
}

//Subfunction
void Renderer::make_rendering(){
  std::shared_ptr<vk::structure::Render> render = std::make_shared<vk::structure::Render>();
  //---------------------------
say("start rendering");
  //Recording
  if(!vk_graphical->acquire_swapchain_image(*render)) return;
  vk_renderpass->record_all_renderpass(*render);
  vk_graphical->copy_to_swapchain(*render);

  //Submission
  vk_submission->submit_rendering(render);

  //End rendering
  vk_semaphore->reset_pool();
  vk_pipeline->reset();

  say(render->semaphore->handle);
  say("submited");

  //---------------------------
}

}
