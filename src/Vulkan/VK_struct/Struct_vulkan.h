#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Namespace.h>
#include <string>


namespace vk::structure{

struct Vulkan{
  //---------------------------

  Vulkan(utl::Node* node_utility){
    utl::element::Window* utl_window = node_utility->get_utl_window();
    this->window.glfw_window = utl_window->get_window();
    this->cpu_profiler = node_utility->get_cpu_profiler();
    this->gpu_profiler = node_utility->get_gpu_profiler();
  }

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

  //---------------------------
};

}
