#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Fence;}
namespace vk::synchro{class Fence;}
namespace vk::instance{class Query;}


namespace vk::queue{

class Transfer
{
public:
  //Constructor / Destructor
  Transfer(vk::structure::Vulkan* vk_struct);
  ~Transfer();

public:
  //Main functions
  void start_thread();
  void run_thread();
  void wait_for_idle();

  //Command
  void wait_for_command();
  void add_command(vk::structure::Command_buffer* command);
  void process_command();

  //Submission
  void build_submission();
  void make_submission();
  void post_submission();

  inline bool is_queue_idle(){return queue_idle;}

private:
  vk::structure::Vulkan* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  std::vector<vk::structure::Command_buffer*> vec_command_prepa;
  std::vector<vk::structure::Command_buffer*> vec_command_onrun;
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::thread thread;
  bool thread_running = false;
  bool queue_idle = true;
  bool queue_standby = false;
};

}
