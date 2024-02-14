#pragma once

#include <Vulkan/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>
#include <string>


namespace vk::structure{

struct Vulkan{
  //---------------------------

  //Constructor
  Vulkan(utl::Node* node_utility){
    prf::Node* node_profiler = node_utility->get_node_profiler();
    prf::Manager* profiler_manager = node_profiler->get_profiler_manager();
    utl::element::Window* utl_window = node_utility->get_utl_window();

    this->window.glfw_window = utl_window->get_window();
    this->tasker_cpu = profiler_manager->get_tasker_cpu();
    this->tasker_gpu = profiler_manager->get_tasker_gpu();
    this->prf_vulkan = node_profiler->get_vulkan_manager();
  }

  //General
  std::string name;
  int UID = 0;

  //Structure
  vk::structure::Render render;
  vk::structure::Window window;
  vk::structure::Instance instance;
  vk::structure::Device device;
  vk::structure::Swapchain swapchain;
  vk::structure::Data data;
  vk::structure::Parameter param;
  vk::structure::Pool pools;
  vk::structure::Command command;

  //Queue
  vk::queue::Transfer* transfer;
  vk::queue::Graphics* graphics;

  //Profiling
  prf::Tasker* tasker_cpu;
  prf::Tasker* tasker_gpu;
  prf::vulkan::Manager* prf_vulkan;

  //---------------------------
};

}
