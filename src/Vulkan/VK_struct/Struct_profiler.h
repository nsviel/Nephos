#pragma once

#include <Vulkan/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::structure{

struct Profiler{
  //---------------------------

  Profiler(prf::Node* node_profiler){
    prf::Manager* prf_manager = node_profiler->get_prf_manager();
    prf::graph::Profiler* profiler = prf_manager->get_profiler_main();

    this->tasker_main = profiler->fetch_tasker("cpu");
    this->tasker_gpu = profiler->fetch_tasker("gpu");
    this->prf_vulkan = prf_manager->get_profiler_vulkan();
    this->prf_vulkan->add_thread("Main");
  }

  prf::graph::Tasker* tasker_main;
  prf::graph::Tasker* tasker_gpu;
  prf::vulkan::Profiler* prf_vulkan;

  //---------------------------
};

}
