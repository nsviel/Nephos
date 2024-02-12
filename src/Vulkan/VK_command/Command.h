#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command;}


namespace vk::command{

class Command
{
public:
  //Constructor / Destructor
  Command(vk::structure::Vulkan* struct_vulkan);
  ~Command();

public:
  //Main function
  void submit_command_thread(vk::structure::Command* command);
  void submit_command(vk::structure::Command* commands);

  //Subfunction
  void prepare_submission(vk::structure::Command* command);
  void queue_submission();
  void wait_and_reset(vk::structure::Command* command);

private:
  vk::structure::Vulkan* struct_vulkan;

  std::thread thread;
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;
  std::vector<VkSemaphore> vec_semaphore_processing;
  std::vector<VkSemaphore> vec_semaphore_done;
  VkFence fence = VK_NULL_HANDLE;
};

}
