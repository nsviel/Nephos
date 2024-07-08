#pragma once

#include <Utility/Element/Thread/Worker.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <thread>
#include <mutex>

namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::synchro::structure{class Fence;}
namespace vk::synchro{class Fence;}
namespace vk::instance{class Query;}


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
  void wait_for_idle();

  //Command
  void wait_for_command();
  void add_command(vk::structure::Command_buffer* command);
  void process_command();

  //Submission
  void build_submission(std::vector<VkSubmitInfo>& vec_info);
  void make_submission(std::vector<VkSubmitInfo>& vec_info);
  void post_submission();

  inline bool is_thread_idle(){return thread_idle;}

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  std::vector<vk::structure::Command_buffer*> vec_command_prepa;
  std::vector<vk::structure::Command_buffer*> vec_command_onrun;
  std::mutex mutex;
  bool thread_idle = true;
};

}
