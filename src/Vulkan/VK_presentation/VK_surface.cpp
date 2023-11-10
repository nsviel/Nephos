#include "VK_surface.h"

#include <VK_main/VK_engine.h>
#include <VK_main/Struct_vulkan.h>


//Constructor / Destructor
VK_surface::VK_surface(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;

  //---------------------------
}
VK_surface::~VK_surface(){}

//Main function
void VK_surface::init_window(){
  //---------------------------

  this->window_extensions();

  //---------------------------
}
void VK_surface::init_surface(){
  //---------------------------



  VkResult result = glfwCreateWindowSurface(struct_vulkan->instance.instance, struct_vulkan->window.glfw_window, nullptr, &struct_vulkan->window.surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}
void VK_surface::clean_surface(){
  //---------------------------

  vkDestroySurfaceKHR(struct_vulkan->instance.instance, struct_vulkan->window.surface, nullptr);

  //---------------------------
}

//Subfunction
void VK_surface::check_for_resizing(){
  static vec2 window_dim = struct_vulkan->window.window_dim;
  //---------------------------

  bool is_resized = false;
  vec2 last_dim = struct_vulkan->window.window_dim;
  if(last_dim.x != window_dim.x || last_dim.y != window_dim.y){
    is_resized = true;
    window_dim = last_dim;
  }

  //---------------------------
  struct_vulkan->window.is_resized = is_resized;
}
void VK_surface::window_extensions(){
  //---------------------------

  uint32_t glfw_extension_nb = 0;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_nb);
  vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_nb);

  for(int i=0; i<extensions.size(); i++){
    struct_vulkan->instance.extension.push_back(extensions[i]);
  }

  //---------------------------
}
