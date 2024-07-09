#pragma once

#include <Utility/Element/Thread/Worker.h>
#include <queue>

namespace vk{class Structure;}
namespace vk::command::structure{class Set;}
namespace vk::queue::presentation{class Submission;}


namespace vk::queue::presentation{

class Thread : public utl::thread::Worker
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
  void add_command(vk::command::structure::Set* set);

private:
  vk::Structure* vk_struct;
  vk::queue::presentation::Submission* vk_submission;

  std::queue<vk::command::structure::Set*> queue;
};

}