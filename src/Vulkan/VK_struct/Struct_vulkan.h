#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <string>


namespace vk::structure{

struct Vulkan{
  //---------------------------

  Vulkan(utl::Node* node_utility){
    prf::Node* node_profiler = node_utility->get_node_profiler();
    utl::element::Window* utl_window = node_utility->get_utl_window();
    this->window.glfw_window = utl_window->get_window();
    this->tasker_cpu = node_profiler->get_tasker_cpu();
    this->tasker_gpu = node_profiler->get_tasker_gpu();
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
  prf::Tasker* tasker_cpu;
  prf::Tasker* tasker_gpu;

  //---------------------------
};

}
