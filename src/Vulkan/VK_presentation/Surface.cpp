#include "Surface.h"

#include <Vulkan/Namespace.h>


namespace vk::presentation{

//Constructor / Destructor
Surface::Surface(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Surface::~Surface(){}

//Main function
void Surface::init(){
  //---------------------------

  this->compute_window_dim();
  VkResult result = glfwCreateWindowSurface(vk_struct->instance.instance, vk_struct->window.handle, nullptr, &vk_struct->window.surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}
void Surface::clean(){
  //---------------------------

  vkDestroySurfaceKHR(vk_struct->instance.instance, vk_struct->window.surface, nullptr);

  //---------------------------
}

//Subfunction
vec2 Surface::compute_window_dim(){
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(vk_struct->window.handle, &width, &height);
  vk_struct->window.dimension = vec2(width, height);

  //---------------------------
  return vk_struct->window.dimension;
}
void Surface::check_for_resizing(){
  static vec2 window_dim = vk_struct->window.dimension;
  //---------------------------

  bool is_resized = false;
  vec2 last_dim = compute_window_dim();
  if(last_dim.x != window_dim.x || last_dim.y != window_dim.y){
    is_resized = true;
    window_dim = last_dim;
  }

  //---------------------------
  vk_struct->window.resized = is_resized;
}

}
