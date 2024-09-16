#pragma once

#include <Vulkan/VK_command/Structure/Command_buffer.h>
#include <vulkan/vulkan.h>
#include <memory>


namespace vk::structure{

struct Command{
  //---------------------------

  //Command
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = std::make_shared<vk::structure::Command_buffer>();
  VkPipelineStageFlags wait_stage = 0;

  //Synchronization
  VkSemaphore semaphore_wait = VK_NULL_HANDLE;
  VkSemaphore semaphore_done = VK_NULL_HANDLE;

  //---------------------------
};

}
