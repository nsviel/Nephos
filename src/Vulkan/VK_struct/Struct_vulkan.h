#pragma once

#include <VK_struct/Namespace.h>
#include <string>


namespace vk::structure{

struct Struct_vulkan{
  //---------------------------

  std::string name;
  vk::structure::Render render;
  vk::structure::Window window;
  vk::structure::Instance instance;
  vk::structure::Device device;
  vk::structure::Swapchain swapchain;
  vk::structure::Info info;
  vk::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pool;
  vk::structure::Synchro synchro;

  Struct_vulkan(GLFWwindow* window){
    this->window.glfw_window = window;
  }

  //---------------------------
};

}
