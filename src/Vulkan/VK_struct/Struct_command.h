#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_struct/Namespace.h>


namespace vk::structure{

struct Command{
  //---------------------------

  //Command
  std::vector<vk::structure::Command_buffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;
  int nb_command_buffer = 100;

  //Synchronization
  std::vector<VkSemaphore> vec_semaphore_wait;
  std::vector<VkSemaphore> vec_semaphore_done;
  VkFence fence = VK_NULL_HANDLE;

  //---------------------------
};

}
