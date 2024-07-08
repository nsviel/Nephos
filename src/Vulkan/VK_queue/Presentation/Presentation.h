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


namespace vk::queue{

class Presentation
{
public:
  //Constructor / Destructor
  Presentation(vk::Structure* vk_struct);
  ~Presentation();

public:
  //Main function
  void wait_for_idle();
  bool acquire_next_image(VkSemaphore& semaphore);
  void image_presentation(VkSemaphore& semaphore);
  void add_presentation_command(std::vector<vk::structure::Command*> vec_command);

  //Subfunction
  void submit_presentation(VkSemaphore& semaphore);
  void next_frame_ID();

  inline bool is_thread_idle(){return thread_idle;}

private:
  vk::Structure* vk_struct;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::GLFW* vk_window;

  bool thread_idle = true;
};

}
