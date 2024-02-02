#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Namespace.h>
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
  vk::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pool;
  vk::structure::Synchro synchro;
  utl::element::Profiler* cpu_profiler;
  utl::element::Profiler* gpu_profiler;

  Vulkan(GLFWwindow* window){
    this->window.glfw_window = window;
  }

  //---------------------------
};

}
