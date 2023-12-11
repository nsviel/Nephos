#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


struct Struct_vk_swapchain{
  //---------------------------

  //Swapchain element
  VkSwapchainKHR swapchain;
  VkSurfaceFormatKHR format;
  VkPresentModeKHR presentation_mode;

  //Swapchain image
  vector<VkImage> vec_swapchain_image;
  uint32_t max_nb_frame;

  //Swapchain frame
  vk::structure::Struct_vk_frame* get_frame_presentation(){return vec_frame[frame_presentation_ID];}
  uint32_t frame_presentation_ID = 0;
  std::vector<vk::structure::Struct_vk_frame*> vec_frame;

  //---------------------------
};
