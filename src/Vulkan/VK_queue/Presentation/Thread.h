#pragma once

#include <Utility/Element/Thread/Worker.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <queue>

namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Surface;}
namespace vk{class Structure;}
namespace vk::synchro::structure{class Fence;}
namespace vk::window{class GLFW;}
namespace vk::structure{class Command;}
namespace vk::command::structure{class Set;}
namespace vk::queue::presentation{class Submission;}
namespace vk::synchro{class Fence;}


namespace vk::queue::presentation{

class Thread : public utl::thread::Worker
{
public:
  //Constructor / Destructor
  Thread(vk::Structure* vk_struct);
  ~Thread();

public:
  //Main function
  void thread_init();
  void thread_loop();

  //Subfunction
  void add_command(vk::command::structure::Set* set);

private:
  vk::Structure* vk_struct;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::GLFW* vk_window;
  vk::queue::presentation::Submission* vk_submission;
  vk::synchro::Fence* vk_fence;

  std::queue<vk::command::structure::Set*> queue;
};

}
