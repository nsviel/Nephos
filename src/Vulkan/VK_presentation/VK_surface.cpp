#include "VK_surface.h"
#include <VK_main/VK_engine.h>
#include "../VK_struct/struct_vulkan.h"

#include <ELE_window/Window.h>


//Constructor / Destructor
VK_surface::VK_surface(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->window = vk_engine->get_window();

  //---------------------------
}
VK_surface::~VK_surface(){}

//Main function
void VK_surface::init_window(){
  //---------------------------

  struct_vulkan->window.windowManager = window;
  this->get_required_extensions();

  //---------------------------
}
void VK_surface::create_window_surface(){
  //---------------------------

  window->create_window_surface(struct_vulkan->instance.instance, struct_vulkan->window.surface);

  //---------------------------
}
void VK_surface::clean_surface(){
  //---------------------------

  vkDestroySurfaceKHR(struct_vulkan->instance.instance, struct_vulkan->window.surface, nullptr);

  //---------------------------
}

//Subfunction
void VK_surface::check_for_resizing(){
  static vec2 window_dim = window->compute_window_dim();
  bool is_resized = false;
  //---------------------------

  //ICI PROBLEM QUAND TRANSLATION TO WINDOW CLASS !!!
  vec2 dim = window->compute_window_dim();
  if(dim.x != window_dim.x || dim.y != window_dim.y){
    is_resized = true;
    window_dim = dim;
  }

  //---------------------------
  struct_vulkan->window.is_resized = is_resized;
}
void VK_surface::get_required_extensions(){
  //---------------------------

  vector<const char*> extensions = window->get_required_extensions();

  for(int i=0; i<extensions.size(); i++){
    struct_vulkan->instance.extension.push_back(extensions[i]);
  }

  //---------------------------
}
