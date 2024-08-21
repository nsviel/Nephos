#pragma once

#include <Profiler/Hardware/src/Structure/Device.h>
#include <Profiler/Hardware/src/Structure/CPU.h>
#include <Profiler/Hardware/src/Structure/GPU.h>
#include <vector>


namespace prf::hardware{

struct Structure{
  //---------------------------

  std::vector<prf::hardware::structure::Device> vec_device;
  prf::hardware::structure::GPU gpu;
  prf::hardware::structure::CPU cpu;

  //---------------------------
};

}
