#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Frame;}
namespace vk::structure{class Semaphore;}


namespace vk::synchro{

class Semaphore
{
public:
  //Constructor / Destructor
  Semaphore(vk::structure::Vulkan* struct_vulkan);
  ~Semaphore();

public:
  //Main functions
  void init_pool();
  void clean_pool();
  void reset();

  //Semaphore function
  void create_semaphore(vk::structure::Semaphore* semaphore);
  void clean_semaphore(vk::structure::Semaphore* semaphore);

  //Subfunction
  vk::structure::Semaphore* query_free_semaphore();



  //OLD
  //Semaphore function
  void init_frame_semaphore(vk::structure::Frame* frame);
  void clean_frame_semaphore(vk::structure::Frame* frame);

  void create_semaphore(VkSemaphore& semaphore);
  void clean_vec_semaphore(vector<VkSemaphore>& vec_semaphore);
  void clean_semaphore(VkSemaphore& semaphore);

private:
  vk::structure::Vulkan* struct_vulkan;
};

}
