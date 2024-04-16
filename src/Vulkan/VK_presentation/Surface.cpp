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

//Subfunction
bool Surface::check_for_resizing(){
  //---------------------------

  vec2 current_dim = vk_window->get_dimension();
  if(current_dim.x != vk_struct->window.dimension.x || current_dim.y != vk_struct->window.dimension.y){
    vk_struct->window.resized = true;
    return true;
  }

  //---------------------------
  return false;
}

}
