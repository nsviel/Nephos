#pragma once

#include <Utility/Namespace.h>
#include <queue>

namespace vk{class Structure;}
namespace vk::command::structure{class Set;}
namespace vk::queue::presentation{class Submission;}


namespace vk::queue::presentation{

class Thread : public sys::thread::Worker
{
public:
  //Constructor / Destructor
  Thread(vk::Structure* vk_struct);
  ~Thread();

public:
  //Main function
  void thread_init();
  void thread_loop();

  //Subfunction
  void make_rendering_thread();
  void make_rendering();

private:
  vk::Structure* vk_struct;
  vk::queue::presentation::Submission* vk_submission;

  std::queue<bool> queue;
};

}
