#include "Vulkan.h"
#include "VK_engine.h"

#include <Engine.h>


//Constructor / Destructor
Vulkan::Vulkan(Engine* engine){
  //---------------------------

  this->vk_engine = new VK_engine(engine);

  //---------------------------
}
Vulkan::~Vulkan(){}

//Main function
void Vulkan::init(){
  //---------------------------

  vk_engine->init();

  //---------------------------
}
void Vulkan::loop_draw_frame(){
  //---------------------------

  vk_engine->loop_draw_frame();

  //---------------------------
}
void Vulkan::device_wait_idle() {
  //---------------------------

  vk_engine->device_wait_idle();

  //---------------------------
}
void Vulkan::clean(){
  //---------------------------

  vk_engine->clean();

  //---------------------------
}
