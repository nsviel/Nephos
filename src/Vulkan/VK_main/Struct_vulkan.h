#ifndef STRUCT_VULKAN_H
#define STRUCT_VULKAN_H

#include <VK_struct/Struct_window.h>
#include <VK_struct/Struct_instance.h>
#include <VK_struct/Struct_device.h>
#include <VK_struct/Struct_swapchain.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_info.h>
#include <VK_struct/Struct_entity.h>
#include <VK_struct/Struct_param.h>
#include <VK_struct/Struct_pool.h>
#include <VK_struct/Struct_render.h>
#include <VK_struct/Struct_synchro.h>
#include <VK_struct/Struct_data.h>
#include <string>


struct Struct_vulkan{
  //---------------------------

  std::string name;
  Struct_render render;
  Struct_window window;
  Struct_instance instance;
  Struct_device device;
  Struct_swapchain swapchain;
  Struct_info info;
  Struct_data data;
  Struct_param param;
  Struct_pool pool;
  Struct_synchro synchro;

  //---------------------------
};

#endif
