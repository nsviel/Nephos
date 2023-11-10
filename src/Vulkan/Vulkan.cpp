#include "Vulkan.h"

#include <VK_main/Struct_vulkan.h>
#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_render.h>
#include <VK_main/VK_info.h>


//Constructor / Destructor
Vulkan::Vulkan(ELE_window* window){
  //---------------------------

  this->struct_vulkan = new Struct_vulkan();
  this->vk_engine = new VK_engine(struct_vulkan, window);
  this->vk_imgui = new VK_imgui(struct_vulkan);
  this->vk_render = new VK_render(struct_vulkan);
  this->vk_info = new VK_info(struct_vulkan);

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

  vk_engine->loop();
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
  Struct_vulkan* struct_vulkan = struct_vulkan;
  //---------------------------

  vk_engine->set_ele_window(ele_window);
  struct_vulkan->param.headless_mode = headless;

  //---------------------------
}
