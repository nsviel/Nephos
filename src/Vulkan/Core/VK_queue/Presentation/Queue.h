#pragma once

#include <Vulkan/Core/VK_queue/Structure/Base.h>
#include <queue>

namespace vk{class Structure;}
namespace vk::commandbuffer::structure{class Set;}
namespace vk::draw{class Renderer;}


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

private:
  vk::Structure* vk_struct;
  vk::draw::Renderer* vk_pipeline;

  std::queue<bool> queue;
};

}
