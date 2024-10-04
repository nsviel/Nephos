#pragma once

#include <Vulkan/Core/VK_queue/Structure/Base.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <queue>

namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::queue::transfer{class Submission;}


namespace vk::queue::transfer{

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
  void add_command(std::shared_ptr<vk::structure::Command_buffer> command_buffer);

private:
  vk::Structure* vk_struct;
  vk::queue::transfer::Submission* vk_submission;

  std::queue<std::shared_ptr<vk::structure::Command_buffer>> queue;
};

}
