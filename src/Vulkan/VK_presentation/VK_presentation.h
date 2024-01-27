#pragma once

#include <Utility/Specific/common.h>

namespace vk::presentation{class VK_swapchain;}
namespace vk::presentation{class VK_surface;}
namespace vk::structure{class Vulkan;}


namespace vk::presentation{

class VK_presentation
{
public:
  //Constructor / Destructor
  VK_presentation(vk::structure::Vulkan* struct_vulkan);
  ~VK_presentation();

public:
  //Main functions
  void acquire_next_image(VkSemaphore& semaphore);
  void image_presentation(VkSemaphore& semaphore, VkFence& fence);

  //Subfunction
  void submit_presentation(VkSemaphore& semaphore);
  void next_frame_ID();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::presentation::VK_surface* vk_surface;
  vk::presentation::VK_swapchain* vk_swapchain;
};

}
