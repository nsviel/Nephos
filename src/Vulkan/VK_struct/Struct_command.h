#pragma once

#include <Utility/Specific/Common.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/Struct_fence.h>


namespace vk::structure{

struct Command{
  //---------------------------

  //Command
  vk::structure::Command_buffer* command_buffer = nullptr;
  VkPipelineStageFlags wait_stage = 0;

  //Synchronization
  VkSemaphore semaphore_wait = VK_NULL_HANDLE;
  VkSemaphore semaphore_done = VK_NULL_HANDLE;

  //---------------------------
};

}
