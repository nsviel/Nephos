#ifndef VK_PARAM_H
#define VK_PARAM_H

#include <VK_struct/Struct_window.h>
#include <VK_struct/Struct_instance.h>
#include <VK_struct/Struct_device.h>
#include <VK_struct/Struct_swapchain.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_info.h>
#include <VK_struct/Struct_data.h>
#include <VK_struct/Struct_param.h>
#include <VK_struct/Struct_pool.h>
#include <VK_struct/Struct_render.h>
#include <VK_struct/Struct_synchro.h>

#include <vector>
#include <list>


struct Struct_vulkan{
  //---------------------------

  Struct_render render;
  Struct_window window;
  Struct_instance instance;
  Struct_device device;
  Struct_swapchain swapchain;
  Struct_info info;
  Struct_data canvas;
  Struct_param param;
  Struct_pool pool;
  Struct_synchro synchro;

  std::vector<Struct_image*> vec_texture;
  std::vector<Struct_device*> vec_physical_device;
  std::list<Struct_data*> list_object;

  //---------------------------
};

#endif
