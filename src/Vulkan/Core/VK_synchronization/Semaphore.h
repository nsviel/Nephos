#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::structure{class Frame;}
namespace vk::structure{class Semaphore;}


namespace vk::synchro{

class Semaphore
{
public:
  //Constructor / Destructor
  Semaphore(vk::Structure* vk_struct);
  ~Semaphore();

public:
  //Main function
  void init_pool();
  void clean_pool();
  void reset_pool();

  //Subfunction
  void create_semaphore(vk::structure::Semaphore& semaphore);
  void clean_semaphore(vk::structure::Semaphore& semaphore);
  void reset_semaphore(vk::structure::Semaphore& semaphore);
  std::shared_ptr<vk::structure::Semaphore> query_free_semaphore();

private:
  vk::Structure* vk_struct;
};

}
