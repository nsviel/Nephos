#pragma once

#include <Vulkan/Core/VK_queue/Structure/Base.h>
#include <queue>

namespace vk{class Structure;}
namespace vk::commandbuffer::structure{class Set;}
namespace vk::queue::presentation{class Submission;}
namespace vk::draw{class Renderer;}
namespace vk::structure{class Render;}


namespace vk::queue::presentation{

class Command : public vk::queue::Base
{
public:
  //Constructor / Destructor
  Command(vk::Structure* vk_struct);
  ~Command();

public:
  //Main function
  void thread_init();
  void thread_loop();

  //Subfunction
  void make_rendering_thread();
  void submit_presentation(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::draw::Renderer* vk_pipeline;
  vk::queue::presentation::Submission* vk_submission;

  std::queue<bool> queue;
};

}
