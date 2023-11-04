#include "GPU_render.h"

#include <VK_presentation/VK_surface.h>
#include <VK_main/VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <image/IconsFontAwesome5.h>
#include <ELE_window/Window.h>


//Constructor / Destructor
GPU_render::GPU_render(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();

  //---------------------------
}
GPU_render::~GPU_render(){}

//Main function
