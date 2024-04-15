#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Fence;}
namespace vk::synchro{class Fence;}
namespace vk::instance{class Query;}


namespace vk::queue{

class Graphics
{
public:
  //Constructor / Destructor
  Graphics(vk::structure::Vulkan* vk_struct);
  ~Graphics();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();
  
  //Processing
  void wait_for_idle();
  void wait_for_command();
  void process_command();

  //Command
  void add_command(vk::structure::Command* command);
  void add_graphics(vector<vk::structure::Command*> vec_command);
  void add_presentation(vector<vk::structure::Command*> vec_command);

  //Submission
  void build_submission(vector<VkSubmitInfo>& vec_info, VkSemaphore& done);
  void make_submission(vector<VkSubmitInfo>& vec_info);
  void post_submission(VkSemaphore& semaphore_done);

  inline bool is_thread_idle(){return thread_idle;}

private:
  vk::structure::Vulkan* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  std::vector<vk::structure::Command*> vec_command_onrun;
  std::vector<vk::structure::Command*> vec_command_prepa;
  bool thread_idle = true;
  bool thread_running = false;
  bool with_presentation = false;
  std::thread thread;
};

}
