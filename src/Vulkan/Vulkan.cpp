#include "Vulkan.h"

#include <VK_main/VK_engine.h>
#include <VK_main/VK_imgui.h>
#include <VK_main/VK_render.h>
#include <VK_main/VK_info.h>


//Constructor / Destructor
Vulkan::Vulkan(ELE_window* window){
  //---------------------------

  this->vk_engine = new VK_engine(window);
  this->vk_imgui = vk_engine->get_vk_imgui();
  this->vk_render = vk_engine->get_vk_render();
  this->vk_info = vk_engine->get_vk_info();

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
static int a =0;
a++;
if(a<100);
  vk_render->loop_draw_frame();

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
