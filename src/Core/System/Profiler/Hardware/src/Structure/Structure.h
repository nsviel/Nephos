#pragma once

#include <Hardware/src/Structure/Device.h>
#include <Hardware/src/Structure/CPU.h>
#include <Hardware/src/Structure/GPU.h>
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
