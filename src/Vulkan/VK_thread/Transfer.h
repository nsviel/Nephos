#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command_buffer;}
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
  void add_command(vk::structure::Command_buffer* command);

  //Subfunction
  void wait_for_command();
  void queue_submission();
  void post_submission();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::synchro::Fence* vk_fence;

  std::vector<vk::structure::Command_buffer*> vec_command_prepa;
  std::vector<vk::structure::Command_buffer*> vec_command_onrun;
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::thread thread;
  bool thread_running = false;
};

}
