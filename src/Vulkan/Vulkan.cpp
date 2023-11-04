#include "Vulkan.h"
#include "VK_main/VK_engine.h"


//Constructor / Destructor
Vulkan::Vulkan(Engine* engine){
  //---------------------------

  this->vk_engine = new VK_engine(engine);
  this->vk_imgui = vk_engine->get_vk_imgui();

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

  vk_engine->loop_draw_frame();

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
