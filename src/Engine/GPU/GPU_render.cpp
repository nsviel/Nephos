#include "GPU_render.h"

#include <Vulkan/Window/VK_surface.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <image/IconsFontAwesome5.h>
#include <Window/Window.h>


//Constructor / Destructor
GPU_render::GPU_render(VK_engine* vk_engine){
  //---------------------------

  this->vk_struct = vk_engine->get_vk_struct();

  //---------------------------
}
GPU_render::~GPU_render(){}

//Main function
