#pragma once

#include <VK_struct/Struct_vk_window.h>
#include <VK_struct/Struct_vk_instance.h>
#include <VK_struct/Device.h>
#include <VK_struct/Struct_vk_swapchain.h>
#include <VK_struct/Struct_vk_renderpass.h>
#include <VK_struct/Struct_vk_info.h>
#include <VK_struct/Namespace.h>
#include <VK_struct/Struct_vk_param.h>
#include <VK_struct/Struct_vk_pool.h>
#include <VK_struct/Struct_vk_render.h>
#include <VK_struct/Struct_vk_synchro.h>
#include <VK_struct/Data.h>
#include <string>


struct Struct_vulkan{
  //---------------------------



  std::string name;
  Struct_vk_render render;
  Struct_vk_window window;
  Struct_vk_instance instance;
  vk::structure::Device device;
  Struct_vk_swapchain swapchain;
  Struct_vk_info info;
  vk::structure::Data data;
  Struct_vk_param param;
  Struct_vk_pool pool;
  Struct_vk_synchro synchro;

  Struct_vulkan(GLFWwindow* window){
    this->window.glfw_window = window;
  }

  //---------------------------
};
