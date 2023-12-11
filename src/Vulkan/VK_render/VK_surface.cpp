#include "VK_surface.h"

#include <VK_struct/Namespace.h>


//Constructor / Destructor
VK_surface::VK_surface(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_surface::~VK_surface(){}

//Main function
void VK_surface::init(){
  //---------------------------

  this->compute_window_dim();
  VkResult result = glfwCreateWindowSurface(struct_vulkan->instance.instance, struct_vulkan->window.glfw_window, nullptr, &struct_vulkan->window.surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}
void VK_surface::clean(){
  //---------------------------

  vkDestroySurfaceKHR(struct_vulkan->instance.instance, struct_vulkan->window.surface, nullptr);

  //---------------------------
}

//Subfunction
vec2 VK_surface::compute_window_dim(){
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(struct_vulkan->window.glfw_window, &width, &height);
  struct_vulkan->window.window_dim = vec2(width, height);

  //---------------------------
  return struct_vulkan->window.window_dim;
}
void VK_surface::check_for_resizing(){
  static vec2 window_dim = struct_vulkan->window.window_dim;
  //---------------------------

  bool is_resized = false;
  vec2 last_dim = compute_window_dim();
  if(last_dim.x != window_dim.x || last_dim.y != window_dim.y){
    is_resized = true;
    window_dim = last_dim;
  }

  //---------------------------
  struct_vulkan->window.is_resized = is_resized;
}
