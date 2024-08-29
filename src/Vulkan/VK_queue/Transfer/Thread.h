#pragma once

#include <Vulkan/VK_queue/Structure/Thread.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <queue>

namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::queue::transfer{class Submission;}


namespace vk::queue::transfer{

class Thread : public vk::queue::Thread
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
  void add_command(vk::structure::Command_buffer* command);

private:
  vk::Structure* vk_struct;
  vk::queue::transfer::Submission* vk_submission;

  std::queue<std::vector<vk::structure::Command_buffer*>> queue;
};

}
