#pragma once

#include <VK_struct/Namespace.h>
#include <string>


struct Struct_vulkan{
  //---------------------------



  std::string name;
  vk::structure::Render render;
  vk::structure::Struct_vk_window window;
  vk::structure::Instance instance;
  vk::structure::Device device;
  vk::structure::Struct_vk_swapchain swapchain;
  vk::structure::Info info;
  vk::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pool;
  vk::structure::Struct_vk_synchro synchro;

  Struct_vulkan(GLFWwindow* window){
    this->window.glfw_window = window;
  }

  //---------------------------
};
