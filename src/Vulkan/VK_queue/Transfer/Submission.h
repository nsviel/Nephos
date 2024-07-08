#pragma once

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

class Submission
{
public:
  //Constructor / Destructor
  Submission(vk::Structure* vk_struct);
  ~Submission();

public:
  //Main function
  void process_command(std::vector<vk::structure::Command_buffer*> vec_command);

  //Submission
  void build_submission(std::vector<vk::structure::Command_buffer*> vec_command, std::vector<VkSubmitInfo>& vec_info);
  void make_submission(std::vector<VkSubmitInfo>& vec_info);
  void post_submission(std::vector<vk::structure::Command_buffer*> vec_command);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  std::mutex mutex;
};

}
