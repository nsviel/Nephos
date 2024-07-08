#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <thread>

namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Surface;}
namespace vk{class Structure;}
namespace vk::synchro::structure{class Fence;}
namespace vk::window{class GLFW;}
namespace vk::structure{class Command;}


namespace vk::queue::presentation{

class Submission
{
public:
  //Constructor / Destructor
  Submission(vk::Structure* vk_struct);
  ~Submission();

public:
  //Main function
  void process_command(VkSemaphore& semaphore);

  //Subfunction
  void submit_presentation(VkSemaphore& semaphore);
  void next_frame_ID();

private:
  vk::Structure* vk_struct;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::GLFW* vk_window;
};

}
