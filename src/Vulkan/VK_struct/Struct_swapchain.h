#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "Struct_frame.h"
#include <ELE_specific/common.h>


struct Struct_swapchain{
  //---------------------------

  //Swapchain element
  VkSwapchainKHR swapchain;

  //Swapchain image
  vector<VkImage> vec_swapchain_image;

  //Swapchain frame
  Struct_frame* get_frame_current(){return vec_frame[frame_current_ID];}
  Struct_frame* get_frame_inflight(){return vec_frame[frame_inflight_ID];}
  uint32_t frame_current_ID = 0;
  uint32_t frame_inflight_ID = 0;
  std::vector<Struct_frame*> vec_frame;

  //---------------------------
};


#endif
