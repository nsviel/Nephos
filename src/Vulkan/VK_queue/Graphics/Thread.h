#pragma once

#include <Utility/Component/Thread/Worker/Worker.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <queue>

namespace vk{class Structure;}
namespace vk::command::structure{class Set;}
namespace vk::structure{class Command;}
namespace vk::queue::graphics{class Submission;}
namespace vk::synchro{class Fence;}
namespace vk::synchro::structure{class Fence;}


namespace vk::queue::graphics{

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
  void add_command(vk::structure::Command* command);
  void add_command(std::vector<vk::structure::Command*> vec_command);
  void add_command(vk::command::structure::Set* set);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::queue::graphics::Submission* vk_submission;

  std::queue<vk::command::structure::Set*> queue;
};

}
