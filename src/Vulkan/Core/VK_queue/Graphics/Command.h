#pragma once

#include <Vulkan/Core/VK_queue/Structure/Base.h>
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>
#include <queue>

namespace vk{class Structure;}
namespace vk::queue::graphics{class Submission;}
namespace vk::synchro{class Fence;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Render;}
namespace vk::structure{class Batch;}
namespace vk::structure{class Command_set;}
namespace vk::structure{class Command;}


namespace vk::queue::graphics{

class Command : public vk::queue::Base
{
public:
  //Constructor / Destructor
  Command(vk::Structure* vk_struct);
  ~Command();

public:
  //Main function
  void thread_init();
  void thread_loop();

  //Subfunction
  void add_command(std::unique_ptr<vk::structure::Command> command);
  void add_command(std::shared_ptr<vk::structure::Render> render);
  void add_command(std::shared_ptr<vk::structure::Batch> batch);

private:
  vk::Structure* vk_struct;
  vk::synchro::Fence* vk_fence;
  vk::queue::graphics::Submission* vk_submission;

  std::queue<std::shared_ptr<vk::structure::Command_set>> queue;
};

}
