#ifndef STRUCT_VK_COMMAND_H
#define STRUCT_VK_COMMAND_H

#include <UTL_specific/common.h>


struct Struct_vk_command{
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


#endif
