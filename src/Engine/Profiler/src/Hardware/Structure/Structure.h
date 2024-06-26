#pragma once

#include <Profiler/src/Hardware/Structure/Device.h>
#include <Profiler/src/Hardware/Structure/CPU.h>
#include <Profiler/src/Hardware/Structure/GPU.h>
#include <vector>


namespace prf::hardware{

struct Structure{
  //---------------------------

  std::vector<prf::hardware::Device> vec_device;
  prf::hardware::GPU gpu;
  prf::hardware::CPU cpu;

  //---------------------------
};

}
