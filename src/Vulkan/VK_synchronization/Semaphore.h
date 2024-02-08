#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Frame;}


namespace vk::synchro{

class Semaphore
{
public:
  //Constructor / Destructor
  Semaphore(vk::structure::Vulkan* struct_vulkan);
  ~Semaphore();

public:
  //Main functions
  void init();
  void clean();

  void init_frame_semaphore(vk::structure::Frame* frame);
  void clean_frame_semaphore(vk::structure::Frame* frame);

  void create_semaphore(VkSemaphore& semaphore);
  void clean_vec_semaphore(vector<VkSemaphore>& vec_semaphore);
  void clean_semaphore(VkSemaphore& semaphore);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
