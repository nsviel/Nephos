#include "Renderer.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render{

//Constructor / Destructor
Renderer::Renderer(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_renderpass = new vk::render::Renderpass(vk_struct);
  this->vk_semaphore = new vk::synchro::Semaphore(vk_struct);
  this->vk_swapchain = new vk::render::Swapchain(vk_struct);
  this->vk_pipeline = new vk::pipeline::compute::Pipeline(vk_struct);

  //---------------------------
}
Renderer::~Renderer(){}

//Main function
void Renderer::loop(){
  std::shared_ptr<vk::structure::Batch> batch = std::make_shared<vk::structure::Batch>();
  //---------------------------

  //Before rendering, check if next image could be acquired
  if(!vk_swapchain->acquire_swapchain_image(batch)) return;

  //If ok, make rendering
  this->make_recording(batch);
  this->make_submission(batch);
  this->make_cleaning();

  //---------------------------
}

//Subfunction
void Renderer::make_recording(std::shared_ptr<vk::structure::Batch> batch){
  //---------------------------

  vk_renderpass->record_all_renderpass(batch);
  vk_swapchain->copy_to_swapchain(batch);

  //---------------------------
}
void Renderer::make_submission(std::shared_ptr<vk::structure::Batch> batch){
  //---------------------------

  vk_struct->core.command.graphics->add_command(batch);

  //---------------------------
}
void Renderer::make_cleaning(){
  //---------------------------

  vk_semaphore->reset_pool();
  vk_pipeline->reset();

  //---------------------------
}

}
