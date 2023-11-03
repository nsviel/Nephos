#ifndef VK_CLASS_H
#define VK_CLASS_H

#include "../VK_struct/struct_frame.h"
#include <ELE_specific/common.h>

class VK_engine;
class struct_vulkan;
class VK_device;


class VK_synchronization
{
public:
  //Constructor / Destructor
  VK_synchronization(VK_engine* vk_engine);
  ~VK_synchronization();

public:
  //Main functions
  void init_frame_sync(Frame* frame);
  void clean_frame_sync(Frame* frame);

  //Synchronization object
  void create_semaphore(VkSemaphore& semaphore);
  void create_fence(VkFence& fence);

  //Deletion function
  void clean_semaphore(VkSemaphore& semaphore);
  void clean_fence(VkFence& fence);

private:
  VK_engine* vk_engine;
  struct_vulkan* vk_struct;
  VK_device* vk_device;

  std::vector<VkSemaphore> semvec_image_available;
  std::vector<VkSemaphore> semvec_render_finish;
  std::vector<VkFence> fenvec_inFlight;
};

#endif
