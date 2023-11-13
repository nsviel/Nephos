#include "Vulkan.h"

#include <UTL_window/UTL_window.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_info.h>


//Constructor / Destructor
Vulkan::Vulkan(UTL_window* window){
  //---------------------------

  this->utl_window = window;
  this->struct_vulkan = new Struct_vulkan();
  this->vk_engine = new VK_engine(struct_vulkan);
  this->vk_imgui = new VK_imgui(struct_vulkan);
  this->vk_info = new VK_info(struct_vulkan);

  //---------------------------
}
Vulkan::~Vulkan(){}

//Main function
void Vulkan::init(){
  //---------------------------

  struct_vulkan->window.glfw_window = utl_window->get_window();
  struct_vulkan->window.window_dim = utl_window->compute_window_dim();

  vk_engine->init();

  //---------------------------
}
void Vulkan::loop(){
  //---------------------------

  struct_vulkan->window.window_dim = utl_window->compute_window_dim();

  vk_engine->loop();

  //---------------------------
}
void Vulkan::clean(){
  //---------------------------

  vk_engine->clean();

  //---------------------------
}
void Vulkan::wait(){
  //---------------------------

  vk_engine->device_wait_idle();

  //---------------------------
}
void Vulkan::param(UTL_window* utl_window, bool headless){
  //---------------------------


  //---------------------------
}
