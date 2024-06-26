#pragma once

#include <Profiler/src/Profiler/Hardware/Structure/Thread.h>
#include <Profiler/src/Profiler/Hardware/Structure/Device.h>
#include <vector>


namespace prf::hardware{

struct Structure{
  //---------------------------

  prf::hardware::Device selected_device;
  std::vector<prf::hardware::Thread> vec_thread;
  std::vector<prf::hardware::Device> vec_device;
  std::vector<prf::hardware::Queue> vec_queue;
  std::mutex mutex;

  //---------------------------
};

}
