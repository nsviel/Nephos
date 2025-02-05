#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <thread>
#include <mutex>

namespace vk{class Structure;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Fence;}
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
  void process_command(vk::structure::Command_buffer& command_buffer);

  //Submission
  void build_submission(vk::structure::Command_buffer& command_buffer, std::vector<VkSubmitInfo>& vec_info);
  void make_submission(std::vector<VkSubmitInfo>& vec_info);
  void post_submission(vk::structure::Command_buffer& command_buffer);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  std::mutex mutex;
};

}
