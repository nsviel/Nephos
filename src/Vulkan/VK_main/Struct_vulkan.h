#pragma once

#include <VK_struct/Struct_vk_window.h>
#include <VK_struct/Instance.h>
#include <VK_struct/Struct_vk_swapchain.h>
#include <VK_struct/Struct_vk_renderpass.h>
#include <VK_struct/Namespace.h>
#include <VK_struct/Parameter.h>
#include <VK_struct/Struct_vk_pool.h>
#include <VK_struct/Struct_vk_render.h>
#include <VK_struct/Struct_vk_synchro.h>
#include <string>


struct Struct_vulkan{
  //---------------------------



  std::string name;
  Struct_vk_render render;
  Struct_vk_window window;
  vk::structure::Instance instance;
  vk::structure::Device device;
  Struct_vk_swapchain swapchain;
  vk::structure::Info info;
  vk::structure::Data data;
  vk::structure::Parameter param;
  Struct_vk_pool pool;
  Struct_vk_synchro synchro;

  Struct_vulkan(GLFWwindow* window){
    this->window.glfw_window = window;
  }

  //---------------------------
};
