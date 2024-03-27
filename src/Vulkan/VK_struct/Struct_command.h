#pragma once

#include <Utility/Specific/Common.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/Struct_fence.h>


namespace vk::structure{

struct Command{
  //---------------------------

  //Command
  std::vector<vk::structure::Command_buffer*> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;

  //Synchronization
  std::vector<VkSemaphore> vec_semaphore_processing;
  std::vector<VkSemaphore> vec_semaphore_done;
  vk::structure::Fence* fence = nullptr;

  //---------------------------
};

}
