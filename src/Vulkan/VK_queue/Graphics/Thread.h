#pragma once

#include <Utility/Element/Thread/Worker.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>

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

  //Subfunction
  void wait_for_command();
  void wait_for_idle();
  void process_command();

  //Command
  void add_command(vk::structure::Command* command);
  void add_graphics(std::vector<vk::structure::Command*> vec_command);
  void add_presentation(std::vector<vk::structure::Command*> vec_command);

  //Submission
  void build_submission(std::vector<VkSubmitInfo>& vec_info, VkSemaphore& done);
  void make_submission(std::vector<VkSubmitInfo>& vec_info);
  void post_submission();

  inline bool is_thread_idle(){return thread_idle;}

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;
  vk::queue::graphics::Submission* vk_submission;

  std::vector<vk::structure::Command*> vec_command_onrun;
  std::vector<vk::structure::Command*> vec_command_prepa;
  std::queue<std::vector<vk::structure::Command*>> queue_command;
  bool thread_idle = true;
  bool with_presentation = false;
  std::mutex mutex;
};

}
