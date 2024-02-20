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
    prf::Manager* prf_manager = node_profiler->get_prf_manager();
    utl::element::Window* utl_window = node_utility->get_utl_window();



    prf::Profiler* profiler = prf_manager->get_profiler_main();


    this->window.glfw_window = utl_window->get_window();
    this->tasker_main = profiler->get_tasker("cpu");
    this->tasker_gpu = profiler->get_tasker("gpu");
    this->prf_vulkan = profiler->get_tasker_vulkan();
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
  vk::structure::Queue_class queue;

  //Profiling
  prf::Tasker* tasker_main;
  prf::Tasker* tasker_gpu;
  prf::vulkan::Manager* prf_vulkan;

  //---------------------------
};

}
