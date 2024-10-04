#include "Submission.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::draw{

//Constructor / Destructor
Submission::Submission(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_swapchain = new vk::presentation::Swapchain(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_fence = new vk::synchro::Fence(vk_struct);

  //---------------------------
}
Submission::~Submission(){}

//Main function
void Submission::submit_rendering(vk::structure::Render& render){
  //---------------------------

  //Rendering
  std::shared_ptr<vk::structure::Command_set> set = std::make_shared<vk::structure::Command_set>();
  set->vec_command = std::move(render.vec_command);
  vk_struct->core.command.graphics->add_command(set);

  set->wait_until_done();

  //---------------------------
}
void Submission::submit_presentation(vk::structure::Render& render){
  //---------------------------

  vk_struct->core.command.presentation->submit_presentation(render);

  //---------------------------
}

}
