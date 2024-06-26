#pragma once

#include <Profiler/src/Profiler/Vulkan/Structure/Thread.h>
#include <Profiler/src/Profiler/Vulkan/Structure/Device.h>
#include <vector>


namespace prf::vulkan{

struct Structure{
  //---------------------------

  prf::vulkan::Device selected_device;
  std::vector<prf::vulkan::Thread> vec_thread;
  std::vector<prf::vulkan::Device> vec_device;

  //---------------------------
};

}
