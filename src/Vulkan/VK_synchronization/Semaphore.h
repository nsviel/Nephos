#pragma once

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Frame;}
namespace vk::synchro::structure{class Semaphore;}


namespace vk::synchro{

class Semaphore
{
public:
  //Constructor / Destructor
  Semaphore(vk::structure::Vulkan* vk_struct);
  ~Semaphore();

public:
  //Pool function
  void init_pool();
  void clean_pool();
  void reset_pool();

  //Semaphore function
  void create_semaphore(vk::synchro::structure::Semaphore* semaphore);
  void clean_semaphore(vk::synchro::structure::Semaphore* semaphore);
  void reset_semaphore(vk::synchro::structure::Semaphore* semaphore);

  //Subfunction
  vk::synchro::structure::Semaphore* query_free_semaphore();

private:
  vk::structure::Vulkan* vk_struct;
};

}
