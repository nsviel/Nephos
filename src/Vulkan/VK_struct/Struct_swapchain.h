#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_frame.h>
#include <UTL_specific/common.h>


struct Struct_swapchain{
  //---------------------------

  //Swapchain element
  VkSwapchainKHR swapchain;
  VkSurfaceFormatKHR format;
  VkPresentModeKHR presentation_mode;

  //Swapchain image
  vector<VkImage> vec_swapchain_image;
  uint32_t max_nb_frame;

  //Swapchain frame
  Struct_frame* get_frame_presentation(){return vec_frame[frame_presentation_ID];}
  uint32_t frame_presentation_ID = 0;
  std::vector<Struct_frame*> vec_frame;

  //---------------------------
};


#endif
