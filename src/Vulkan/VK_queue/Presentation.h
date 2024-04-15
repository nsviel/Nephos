#pragma once

#include <Utility/Specific/Common.h>

namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Surface;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Fence;}


namespace vk::queue{

class Presentation
{
public:
  //Constructor / Destructor
  Presentation(vk::structure::Vulkan* vk_struct);
  ~Presentation();

public:
  //Main functions
  void wait_for_idle();
  bool acquire_next_image(VkSemaphore& semaphore);
  void image_presentation(VkSemaphore& semaphore);
  bool check_for_resizing();

  //Subfunction
  void submit_presentation(VkSemaphore& semaphore);
  void next_frame_ID();

  inline bool is_thread_idle(){return thread_idle;}

private:
  vk::structure::Vulkan* vk_struct;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;

  bool thread_idle = true;
};

}
