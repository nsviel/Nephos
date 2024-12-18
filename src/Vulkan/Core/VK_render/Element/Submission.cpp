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
void Submission::submit_rendering(std::shared_ptr<vk::structure::Render> render){
  //---------------------------

  //Rendering
  vk_struct->core.command.graphics->add_command(render);

  //Presentation
  vk_struct->core.command.presentation->add_command(render);

  //---------------------------
}

}
