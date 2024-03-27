#pragma once

#include <Utility/Specific/Common.h>


namespace prf::vulkan{

struct Queue_family{
  //---------------------------

  int nb_queue = 0;
  bool graphics = 0;
  bool compute = 0;
  bool transfer = 0;
  bool sparseBinding = 0;
  bool presentation = 0;

  //---------------------------
};

struct Device{
  //---------------------------

  //GPU device
  string name;
  bool has_extension_support;
  bool discrete_gpu;
  uint32_t max_image_dim;
  int vendorID;

  //GPU queues
  int ID_family_graphics = -1;
  int ID_family_transfer = -1;
  int ID_family_presentation = -1;
  std::vector<prf::vulkan::Queue_family> vec_queue_family;

  //---------------------------
};

}
