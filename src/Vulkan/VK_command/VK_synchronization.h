#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>
#include <VK_struct/Frame.h>

class Struct_vulkan;


class VK_synchronization
{
public:
  //Constructor / Destructor
  VK_synchronization(Struct_vulkan* struct_vulkan);
  ~VK_synchronization();

public:
  //Main functions
  void init();
  void init_frame_sync(vk::structure::Frame* frame);
  void clean();
  void clean_frame_sync(vk::structure::Frame* frame);

  //Synchronization object
  void create_semaphore(VkSemaphore& semaphore);
  void create_fence(VkFence& fence);

  //Deletion function
  void clean_vec_semaphore(vector<VkSemaphore>& vec_semaphore);
  void clean_semaphore(VkSemaphore& semaphore);
  void clean_vec_fence(vector<VkFence>& vec_fence);
  void clean_fence(VkFence& fence);

private:
  Struct_vulkan* struct_vulkan;
};
