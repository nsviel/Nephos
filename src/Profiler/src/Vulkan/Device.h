#pragma once

#include <Utility/Specific/common.h>


namespace prf::vulkan{

struct Device{
  //---------------------------

  //GPU device
  string name;
  bool has_extension_support;
  uint32_t max_image_dim;
  int vendorID;

  //GPU queues
  int queue_graphics_idx = -1;
  int queue_transfer_idx = -1;
  int queue_presentation_idx = -1;
  uint32_t nb_queue_family = 0;
  uint32_t nb_queue_graphics = 0;
  uint32_t nb_queue_compute = 0;
  uint32_t nb_queue_transfer = 0;
  uint32_t nb_queue_sparseBinding = 0;
  uint32_t nb_queue_presentation = 0;

  //---------------------------
};

}
