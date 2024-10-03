#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::structure{class Fence;}


namespace vk::synchro{

class Fence
{
public:
  //Constructor / Destructor
  Fence(vk::Structure* vk_struct);
  ~Fence();

public:
  //Main function
  void init_pool();
  void clean_pool();

  //Subfunction
  void create_fence(vk::structure::Fence& fence);
  void clean_fence(vk::structure::Fence& fence);
  void reset_fence(vk::structure::Fence& fence);
  bool is_fence_available(vk::structure::Fence& fence);
  std::shared_ptr<vk::structure::Fence> query_free_fence();

private:
  vk::Structure* vk_struct;
};

}
