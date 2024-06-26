#pragma once

#include <Vulkan/VK_command/Structure/Command_buffer.h>
#include <vulkan/vulkan.h>


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
