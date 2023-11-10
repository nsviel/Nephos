#include "Vulkan.h"

#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_render.h>
#include <VK_main/VK_info.h>


//Constructor / Destructor
Vulkan::Vulkan(ELE_window* window){
  //---------------------------

  this->vk_engine = new VK_engine(window);
  this->vk_imgui = new VK_imgui(vk_engine);
  this->vk_render = new VK_render(vk_engine);
  this->vk_info = new VK_info(vk_engine);

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
  Struct_vulkan* struct_vulkan = vk_engine->get_struct_vulkan();
  //---------------------------

  vk_engine->set_ele_window(ele_window);
  struct_vulkan->param.headless_mode = headless;

  //---------------------------
}
