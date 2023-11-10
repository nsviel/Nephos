#include "Vulkan.h"

#include <ELE_window/ELE_window.h>
#include <VK_main/Struct_vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_render.h>
#include <VK_main/VK_info.h>


//Constructor / Destructor
Vulkan::Vulkan(ELE_window* window){
  //---------------------------

  this->ele_window = window;
  this->struct_vulkan = new Struct_vulkan();
  this->vk_engine = new VK_engine(struct_vulkan);
  this->vk_imgui = new VK_imgui(struct_vulkan);
  this->vk_render = new VK_render(struct_vulkan);
  this->vk_info = new VK_info(struct_vulkan);

  //---------------------------
}
Vulkan::~Vulkan(){}

//Main function
void Vulkan::init(){
  //---------------------------

  struct_vulkan->window.glfw_window = ele_window->get_window();
  struct_vulkan->window.window_dim = ele_window->compute_window_dim();

  vk_engine->init();

  //---------------------------
}
void Vulkan::loop(){
  //---------------------------

  struct_vulkan->window.window_dim = ele_window->compute_window_dim();

  vk_render->loop();

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
void Vulkan::param(ELE_window* ele_window, bool headless){
  //---------------------------

  //vk_engine->set_ele_window(ele_window);
  struct_vulkan->param.headless_mode = headless;

  //---------------------------
}
