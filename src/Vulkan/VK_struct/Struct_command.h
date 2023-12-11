#pragma once

#include <Utility/Specific/common.h>


namespace vk::structure{

struct Command{
  //---------------------------

  //Command
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;

  //Synchronization
  std::vector<VkSemaphore> vec_semaphore_wait;
  std::vector<VkSemaphore> vec_semaphore_done;
  VkFence fence = VK_NULL_HANDLE;

  //---------------------------
};

}
