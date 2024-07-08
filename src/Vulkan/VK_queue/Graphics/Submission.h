#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>

namespace vk{class Structure;}
namespace vk::command::structure{class Set;}
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
  void process_command(vk::command::structure::Set set, bool with_presentation);

  //Subfunction
  void build_submission(vk::command::structure::Set& set, std::vector<VkSubmitInfo>& vec_info, VkSemaphore& done);
  void make_submission(vk::command::structure::Set& set, std::vector<VkSubmitInfo>& vec_info);
  void post_submission(vk::command::structure::Set& set);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  bool with_presentation = false;
  std::mutex mutex;
};

}
