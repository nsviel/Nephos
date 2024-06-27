#include "Surface.h"

#include <Vulkan/Namespace.h>


namespace vk::presentation{

//Constructor / Destructor
Surface::Surface(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_window = new vk::window::GLFW(vk_struct);

  //---------------------------
}
Surface::~Surface(){}

//Main function
void Surface::init(){
  //---------------------------

  vk_window->create_surface();

  //---------------------------
}
void Surface::clean(){
  //---------------------------

  vkDestroySurfaceKHR(vk_struct->instance.handle, vk_struct->window.surface, nullptr);

  //---------------------------
}

}