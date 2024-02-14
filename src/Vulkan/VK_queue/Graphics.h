#pragma once

#include <Utility/Specific/common.h>

namespace vk::structure{class Vulkan;}
namespace vk::structure{class Command;}
namespace vk::structure{class Fence;}
namespace vk::synchro{class Fence;}


namespace vk::queue{

class Graphics
{
public:
  //Constructor / Destructor
  Graphics(vk::structure::Vulkan* struct_vulkan);
  ~Graphics();

public:
  //Main functions
  void start_thread();
  void run_thread();
  void add_command(vk::structure::Command* command);

  //Subfunction
  void reset_for_submission();
  void prepare_submission();
  void wait_for_command();
  void queue_submission();
  void post_submission();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::synchro::Fence* vk_fence;

  std::vector<vk::structure::Command*> vec_command_prepa;
  std::vector<vk::structure::Command*> vec_command_onrun;
  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;
  std::vector<VkSemaphore> vec_semaphore_processing;
  std::vector<VkSemaphore> vec_semaphore_done;
  std::thread thread;
  bool thread_running = false;
};

}
