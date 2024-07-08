#pragma once

#include <Utility/Element/Thread/Worker.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

namespace vk{class Structure;}
namespace vk::structure{class Command;}
namespace vk::structure{class Command_buffer;}
namespace vk::synchro::structure{class Fence;}
namespace vk::synchro{class Fence;}
namespace vk::instance{class Query;}
namespace vk::queue::graphics{class Submission;}


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
  void thread_pause(bool value);

  //Subfunction
  void add_command(vk::structure::Command* command);
  void add_graphics(std::vector<vk::structure::Command*> vec_command);
  void add_presentation(std::vector<vk::structure::Command*> vec_command);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;
  vk::queue::graphics::Submission* vk_submission;

  std::queue<std::vector<vk::structure::Command*>> queue;
  bool with_presentation = false;
  bool pause = false;
  std::mutex mutex;
};

}
