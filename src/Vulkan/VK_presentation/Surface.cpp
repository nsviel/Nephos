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
void Surface::check_for_resizing(){
  static vec2 window_dim = vk_struct->window.dimension;
  //---------------------------

  bool is_resized = false;
  vec2 last_dim = vk_window->update_window_dim();
  if(last_dim.x != window_dim.x || last_dim.y != window_dim.y){
    is_resized = true;
    window_dim = last_dim;
  }

  //---------------------------
  vk_struct->window.resized = is_resized;
}

}
