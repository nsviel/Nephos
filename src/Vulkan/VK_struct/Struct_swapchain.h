#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_frame.h>
#include <ELE_specific/common.h>


struct Struct_swapchain{
  //---------------------------

  //Swapchain element
  VkSwapchainKHR swapchain;

  //Swapchain image
  vector<VkImage> vec_swapchain_image;

  //Swapchain frame
  Struct_framebuffer* get_framebuffer_presentation(){return vec_framebuffer[frame_presentation_ID];}
  uint32_t frame_presentation_ID = 0;

  std::vector<Struct_framebuffer*> vec_framebuffer;
  std::vector<Struct_frame*> vec_frame;

  //---------------------------
};


#endif
