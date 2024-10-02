#pragma once

#include <Vulkan/Core/VK_commandbuffer/Structure/Command_buffer.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <string>


namespace vk::structure{

struct Command{
  //---------------------------

  //Command
  std::string name = "";
  std::shared_ptr<vk::structure::Command_buffer> command_buffer = std::make_shared<vk::structure::Command_buffer>();
  VkPipelineStageFlags wait_stage = 0;

  //Synchronization
  VkSemaphore semaphore_wait = VK_NULL_HANDLE;
  VkSemaphore semaphore_done = VK_NULL_HANDLE;

  //---------------------------
};

}
