#pragma once

#include <Utility/Element/Thread/Worker.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <thread>
#include <mutex>

namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::queue::transfer{class Submission;}


namespace vk::queue::transfer{

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
  void add_command(vk::structure::Command_buffer* command);
  void wait_for_command();
  void wait_for_idle();

  inline bool is_thread_idle(){return thread_idle;}

private:
  vk::Structure* vk_struct;
  vk::queue::transfer::Submission* vk_submission;

  std::vector<vk::structure::Command_buffer*> vec_command_prepa;
  std::vector<vk::structure::Command_buffer*> vec_command_onrun;
  std::mutex mutex;
  bool thread_idle = true;
};

}