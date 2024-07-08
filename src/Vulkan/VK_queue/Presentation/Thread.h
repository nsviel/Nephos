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
namespace vk::queue::presentation{class Submission;}


namespace vk::queue::presentation{

class Thread
{
public:
  //Constructor / Destructor
  Thread(vk::Structure* vk_struct);
  ~Thread();

public:
  //Main function
  void wait_for_idle();
  void image_presentation(VkSemaphore& semaphore);

  //Subfunction
  void add_command(std::vector<vk::structure::Command*> vec_command);

  inline bool is_thread_idle(){return thread_idle;}

private:
  vk::Structure* vk_struct;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::GLFW* vk_window;
  vk::queue::presentation::Submission* vk_submission;

  bool thread_idle = true;
};

}
