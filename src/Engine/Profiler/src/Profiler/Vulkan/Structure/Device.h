#pragma once

#include <Profiler/src/Profiler/Vulkan/Structure/Queue.h>
#include <vector>
#include <string>


namespace prf::vulkan{

struct Device{
  //---------------------------

  //GPU device
  std::string name;
  bool has_extension_support;
  bool discrete_gpu;
  uint32_t max_image_dim;
  int vendorID;

  //GPU queues
  int ID_family_graphics = -1;
  int ID_family_transfer = -1;
  int ID_family_presentation = -1;
  std::vector<prf::vulkan::queue::Family> vec_queue_family;

  //---------------------------
};

}
