#pragma once

#include <Vulkan/Core/VK_queue/Structure/Base.h>
#include <queue>

namespace vk{class Structure;}
namespace vk::commandbuffer::structure{class Set;}
namespace vk::queue::presentation{class Submission;}


namespace vk::queue::presentation{

class Queue : public vk::queue::Base
{
public:
  //Constructor / Destructor
  Queue(vk::Structure* vk_struct);
  ~Queue();

public:
  //Main function
  void thread_init();
  void thread_loop();

  //Subfunction
  void make_rendering_thread();
  void make_rendering();

private:
  vk::Structure* vk_struct;
  vk::queue::presentation::Submission* vk_submission;

  std::queue<bool> queue;
};

}
