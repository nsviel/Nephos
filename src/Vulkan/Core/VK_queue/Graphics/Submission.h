#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>

namespace vk{class Structure;}
namespace vk::structure{class Command_set;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Fence;}
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
  void process_command(std::shared_ptr<vk::structure::Command_set> set);

  //Subfunction
  void build_submission(std::shared_ptr<vk::structure::Command_set> set);
  void make_submission(std::shared_ptr<vk::structure::Command_set> set);
  void post_submission(std::shared_ptr<vk::structure::Command_set> set);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::instance::Query* vk_query;

  std::vector<VkSubmitInfo> vec_info;
};

}
