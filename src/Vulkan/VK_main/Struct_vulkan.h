#ifndef STRUCT_VULKAN_H
#define STRUCT_VULKAN_H

#include <VK_struct/Struct_vk_window.h>
#include <VK_struct/Struct_vk_instance.h>
#include <VK_struct/Struct_vk_device.h>
#include <VK_struct/Struct_vk_swapchain.h>
#include <VK_struct/Struct_vk_renderpass.h>
#include <VK_struct/Struct_vk_info.h>
#include <VK_struct/Struct_vk_entity.h>
#include <VK_struct/Struct_vk_param.h>
#include <VK_struct/Struct_vk_pool.h>
#include <VK_struct/Struct_vk_render.h>
#include <VK_struct/Struct_vk_synchro.h>
#include <VK_struct/Struct_vk_data.h>
#include <string>


struct Struct_vulkan{
  //---------------------------

  std::string name;
  Struct_vk_render render;
  Struct_vk_window window;
  Struct_vk_instance instance;
  Struct_vk_device device;
  Struct_vk_swapchain swapchain;
  Struct_vk_info info;
  Struct_vk_data data;
  Struct_vk_param param;
  Struct_vk_pool pool;
  Struct_vk_synchro synchro;

  //---------------------------
};

#endif
