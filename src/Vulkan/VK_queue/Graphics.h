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
  Graphics(vk::structure::Vulkan* struct_vulkan);
  ~Graphics();

public:
  //Main function
  void start_thread();
  void run_thread();
  void add_command(vk::structure::Command* command);
  void add_command(vector<vk::structure::Command*> vec_command);
  void add_command_thread(vk::structure::Command_buffer* command_buffer);
  void add_command_thread(vk::structure::Command* command);
  void wait_for_idle();

  //Subfunction
  void wait_for_command();
  void reset_for_submission();
  void prepare_submission();
  void queue_submission();
  void post_submission();

  inline bool is_queue_idle(){return queue_idle;}

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  std::vector<vk::structure::Command*> vec_command_onrun;
  std::vector<vk::structure::Command*> vec_command_prepa;
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;
  std::vector<VkSemaphore> vec_semaphore_processing;
  std::vector<VkSemaphore> vec_semaphore_done;
  bool queue_idle = true;
  bool queue_standby = false;
  bool thread_running = false;
  std::thread thread;
};

}
