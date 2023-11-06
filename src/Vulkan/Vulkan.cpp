#include "Vulkan.h"
#include "VK_main/VK_engine.h"
#include "VK_main/VK_imgui.h"
#include "VK_main/VK_render.h"


//Constructor / Destructor
Vulkan::Vulkan(Window* window){
  //---------------------------

  this->vk_engine = new VK_engine(window);
  this->vk_imgui = vk_engine->get_vk_imgui();
  this->vk_render = vk_engine->get_vk_render();

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

  vk_render->loop_draw_frame();

  //---------------------------
}
void Vulkan::clean(){
  //---------------------------

  vk_engine->clean();

  //---------------------------
}
void Vulkan::wait_idle() {
  //---------------------------

  vk_engine->device_wait_idle();

  //---------------------------
}
