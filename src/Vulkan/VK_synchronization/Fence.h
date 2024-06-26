#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::synchro::structure{class Fence;}


namespace vk::synchro{

class Fence
{
public:
  //Constructor / Destructor
  Fence(vk::structure::Vulkan* vk_struct);
  ~Fence();

public:
  //Pool function
  void init_pool();
  void clean_pool();

  //Fence function
  void create_fence(vk::synchro::structure::Fence* fence);
  void clean_fence(vk::synchro::structure::Fence* fence);
  void reset_fence(vk::synchro::structure::Fence* fence);

  //Subfunction
  vk::synchro::structure::Fence* query_free_fence();
  bool is_fence_available(vk::synchro::structure::Fence* fence);

private:
  vk::structure::Vulkan* vk_struct;
};

}
