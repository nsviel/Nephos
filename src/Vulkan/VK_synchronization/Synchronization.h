#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Frame;}


namespace vk::synchro{

class Synchronization
{
public:
  //Constructor / Destructor
  Synchronization(vk::structure::Vulkan* struct_vulkan);
  ~Synchronization();

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
  vk::structure::Vulkan* struct_vulkan;
};

}
