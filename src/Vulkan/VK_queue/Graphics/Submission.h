#pragma once

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


namespace vk::queue::graphics{

class Submission
{
public:
  //Constructor / Destructor
  Submission(vk::Structure* vk_struct);
  ~Submission();

public:
  //Main function
  void process_command();

  //Subfunction
  void build_submission(std::vector<VkSubmitInfo>& vec_info, VkSemaphore& done);
  void make_submission(std::vector<VkSubmitInfo>& vec_info);
  void post_submission();

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  std::vector<vk::structure::Command*> vec_command_onrun;
  std::vector<vk::structure::Command*> vec_command_prepa;
  std::queue<std::vector<vk::structure::Command*>> queue_command;

  bool with_presentation = false;
  std::mutex mutex;
};

}
