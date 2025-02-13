#pragma once

#include <Hardware/src/Structure/Queue.h>
#include <stdint.h>
#include <vector>
#include <string>


namespace prf::hardware::structure{

struct Device{
  //---------------------------

  //GPU device
  std::string name;
  bool has_extension_support;
  bool discrete_gpu;
  uint32_t max_image_dim;
  int vendor_ID;

  //GPU queues
  int ID_family_graphics = -1;
  int ID_family_transfer = -1;
  int ID_family_presentation = -1;
  std::vector<prf::hardware::structure::queue::Family> vec_queue_family;

  //GPU info


  //---------------------------
};

}
