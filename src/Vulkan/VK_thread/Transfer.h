#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command;}
namespace vk::structure{class Fence;}
namespace vk::synchro{class Fence;}


namespace vk::thread{

class Transfer
{
public:
  //Constructor / Destructor
  Transfer(vk::structure::Vulkan* struct_vulkan);
  ~Transfer();

public:
  //Main functions
  void start_thread();
  void run_thread();

  //Subfunction
  void wait_for_command();
  void reset_for_submission();
  void prepare_submission(vk::structure::Command* command);
  void queue_submission();
  void wait_and_reset(vk::structure::Command* command);

  inline void add_command(vk::structure::Command* command){vec_command.push_back(command);}

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::synchro::Fence* vk_fence;

  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<vk::structure::Command*> vec_command;
  vk::structure::Fence* fence;
  std::thread thread;
  bool thread_running = false;
};

}
