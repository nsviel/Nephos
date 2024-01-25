#include "Vulkan.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

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

//Parameter function
void Vulkan::param(utl::element::Window* utl_window, bool headless){
  //---------------------------


  //---------------------------
}

}
