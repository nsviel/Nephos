#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


class VK_swapchain;
class VK_surface;


class VK_presentation
{
public:
  //Constructor / Destructor
  VK_presentation(vk::structure::Struct_vulkan* struct_vulkan);
  ~VK_presentation();

public:
  //Main functions
  void acquire_next_image(VkSemaphore& semaphore);
  void image_presentation(VkSemaphore& semaphore, VkFence& fence);

  //Subfunction
  void submit_presentation(VkSemaphore& semaphore);
  void next_frame_ID();

private:
  vk::structure::Struct_vulkan* struct_vulkan;
  VK_surface* vk_surface;
  VK_swapchain* vk_swapchain;
};
