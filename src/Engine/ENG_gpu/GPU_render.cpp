#include "GPU_render.h"

#include <VK_window/VK_surface.h>
#include <VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <image/IconsFontAwesome5.h>
#include <ELE_window/Window.h>


//Constructor / Destructor
GPU_render::GPU_render(VK_engine* vk_engine){
  //---------------------------

  this->vk_struct = vk_engine->get_vk_struct();

  //---------------------------
}
GPU_render::~GPU_render(){}

//Main function
