#include "VK_render.h"

#include <VK_main/VK_engine.h>
#include <VK_drawing/VK_drawing.h>
#include <VK_struct/struct_vulkan.h>
#include <ELE_specific/FPS_counter.h>

//Constructor / Destructor
VK_render::VK_render(VK_engine* vk_engine){
  //---------------------------

  this->vk_drawing = vk_engine->get_vk_drawing();
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->fps_counter = new FPS_counter(100);

  //---------------------------
}
VK_render::~VK_render(){}

//Main function
void VK_render::loop_draw_frame(){
  //---------------------------

  vk_drawing->draw_frame();

  //---------------------------
  fps_counter->update();
  struct_vulkan->time.engine_fps = fps_counter->get_fps();
}
