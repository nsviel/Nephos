#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <string>


namespace vk::structure{

struct Vulkan{
  //---------------------------

  std::string name;
  vk::structure::Render render;
  vk::structure::Window window;
  vk::structure::Instance instance;
  vk::structure::Device device;
  vk::structure::Swapchain swapchain;
  vk::structure::Profiler profiler;
  vk::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pool;
  vk::structure::Synchro synchro;

  Vulkan(GLFWwindow* window){
    this->window.glfw_window = window;
  }

  //---------------------------
};

}
