#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command;}
namespace vk::structure{class Fence;}
namespace vk::synchro{class Fence;}


namespace vk::command{

class Command
{
public:
  //Constructor / Destructor
  Command(vk::structure::Vulkan* struct_vulkan);
  ~Command();

public:
  //Main function
  void submit_vec_command();
  void submit_command_thread(vk::structure::Command* command);
  void submit_command(vk::structure::Command* command, vk::structure::Fence* fence);

  //Subfunction
  void reset_for_submission();
  void prepare_submission(vk::structure::Command* command, vk::structure::Fence* fence);
  void queue_submission();
  void wait_and_reset(vk::structure::Command* command);

  inline void add_command_to_submit(vk::structure::Command* command){this->vec_command.push_back(command);}

private:
  vk::structure::Vulkan* struct_vulkan;
  vector<vk::structure::Command*> vec_command;
  vk::synchro::Fence* vk_fence;

  std::thread thread;
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;
  std::vector<VkSemaphore> vec_semaphore_processing;
  std::vector<VkSemaphore> vec_semaphore_done;
  VkFence fence = VK_NULL_HANDLE;
};

}
