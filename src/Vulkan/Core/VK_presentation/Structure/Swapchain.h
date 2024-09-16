#pragma once

#include <Vulkan/Core/VK_presentation/Structure/Frame.h>
#include <vulkan/vulkan.h>
#include <vector>


namespace vk::structure{

struct Swapchain{
  //---------------------------

  //Swapchain element
  VkSwapchainKHR handle = VK_NULL_HANDLE;
  VkSurfaceFormatKHR format = {};
  VkPresentModeKHR presentation_mode = VK_PRESENT_MODE_FIFO_KHR;
  VkFormat required_image_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_B8G8R8A8_SRGB
  
  //Swapchain frame
  uint32_t current_ID = 0;
  uint32_t max_frame = 0;
  std::vector<VkImage> vec_image;
  std::vector<vk::structure::Frame*> vec_frame;

  vk::structure::Frame* get_frame_presentation(){return vec_frame[current_ID];}

  //---------------------------
};

}
