#ifndef STRUCT_COMMAND_H
#define STRUCT_COMMAND_H

#include <ELE_specific/common.h>


struct Struct_command{
  //---------------------------

  VkCommandBuffer command_buffer;
  VkPipelineStageFlags wait_stage;

  VkSemaphore semaphore_wait;
  VkSemaphore semaphore_done;
  VkFence fence = VK_NULL_HANDLE;

  //---------------------------
};

struct Struct_commands{
  //---------------------------

  //Command
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;

  //Synchronization
  std::vector<VkSemaphore> vec_semaphore_rp_wait;
  std::vector<VkSemaphore> vec_semaphore_render;
  VkFence fence = VK_NULL_HANDLE;

  //---------------------------
};


#endif
