#pragma once

#include <Utility/Specific/common.h>


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
  uint32_t max_image_dim;
  int vendorID;

  //GPU queues
  int queue_family_graphics_idx = -1;
  int queue_family_transfer_idx = -1;
  int queue_family_presentation_idx = -1;
  std::vector<prf::vulkan::Queue_family> vec_queue_family;

  //---------------------------
};

}
