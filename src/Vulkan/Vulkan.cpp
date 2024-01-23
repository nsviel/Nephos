#include "Vulkan.h"

#include <Vulkan/VK_main/VK_engine.h>
#include <Vulkan/VK_main/VK_imgui.h>
#include <Vulkan/VK_main/VK_info.h>
#include <Vulkan/VK_main/VK_texture.h>


//Constructor / Destructor
Vulkan::Vulkan(GLFWwindow* window){
  //---------------------------

  this->struct_vulkan = new vk::structure::Vulkan(window);
  this->vk_engine = new VK_engine(struct_vulkan);
  this->vk_imgui = new VK_imgui(struct_vulkan);
  this->vk_info = new VK_info(struct_vulkan);
  this->vk_texture = new VK_texture(struct_vulkan);

  //---------------------------
}
Vulkan::~Vulkan(){}

//Main function
void Vulkan::init(){
  //---------------------------

  vk_engine->init();

  //---------------------------
}
void Vulkan::loop(){
  //---------------------------

  //struct_vulkan->window.window_dim = utl_window->compute_window_dim();

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
void Vulkan::param(utl::element::Window* utl_window, bool headless){
  //---------------------------


  //---------------------------
}
