#pragma once

#include <Utility/Specific/common.h>

namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Surface;}
namespace vk::structure{class Vulkan;}


namespace vk::presentation{

class Presentation
{
public:
  //Constructor / Destructor
  Presentation(vk::structure::Vulkan* struct_vulkan);
  ~Presentation();

public:
  //Main functions
  void acquire_next_image(VkSemaphore& semaphore);
  void image_presentation(VkSemaphore& semaphore, VkFence& fence);

  //Subfunction
  void submit_presentation(VkSemaphore& semaphore);
  void next_frame_ID();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;
};

}
