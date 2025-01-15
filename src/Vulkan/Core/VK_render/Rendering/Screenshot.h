#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::pipeline::compute{class Pipeline;}
namespace vk::draw{class Renderpass;}
namespace vk::draw{class Swapchain;}
namespace vk::synchro{class Semaphore;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Semaphore;}
namespace vk::structure{class Command;}
namespace vk::structure{class Batch;}
namespace vk::structure{class Command_set;}


namespace vk::draw{

class Screenshot
{
public:
  //Constructor / Destructor
  Screenshot(vk::Structure* vk_struct);
  ~Screenshot();

public:
  //Main function
  void make_screenshot();

private:
  vk::Structure* vk_struct;
  vk::draw::Renderpass* vk_renderpass;
  vk::synchro::Semaphore* vk_semaphore;
  vk::draw::Swapchain* vk_swapchain;
  vk::pipeline::compute::Pipeline* vk_pipeline;
};

}
