#pragma once

#include <Utility/Specific/common.h>
#include <Vulkan/VK_struct/Namespace.h>


namespace vk::structure{

struct Command{
  //---------------------------

  //Command
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;

  //Synchronization
  std::vector<VkSemaphore> vec_semaphore_processing;
  std::vector<VkSemaphore> vec_semaphore_done;
  vk::structure::Fence* fence = nullptr;

  //---------------------------
};

}
