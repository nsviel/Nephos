#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Frame{
  //---------------------------

  vk::structure::Image color;

  //---------------------------
};

struct Swapchain{
  //---------------------------

  //Swapchain element
  VkSwapchainKHR handle = VK_NULL_HANDLE;
  VkSurfaceFormatKHR format = {};
  VkPresentModeKHR presentation_mode = VK_PRESENT_MODE_FIFO_KHR;

  //Swapchain frame
  uint32_t current_ID = 0;
  uint32_t max_frame = 0;
  std::vector<VkImage> vec_image;
  std::vector<vk::structure::Frame*> vec_frame;

  vk::structure::Frame* get_frame_presentation(){return vec_frame[current_ID];}

  //---------------------------
};

}
