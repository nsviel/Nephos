#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::pipeline::compute{class Pipeline;}
namespace vk::render{class Renderpass;}
namespace vk::render{class Swapchain;}
namespace vk::synchro{class Semaphore;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Semaphore;}
namespace vk::structure{class Command;}
namespace vk::structure{class Batch;}
namespace vk::structure{class Command_set;}


namespace vk::render{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(vk::Structure* vk_struct);
  ~Renderer();

public:
  //Main function
  void loop();

  //Subfunction
  void make_recording(std::shared_ptr<vk::structure::Batch> batch);
  void make_submission(std::shared_ptr<vk::structure::Batch> batch);
  void make_cleaning();

private:
  vk::Structure* vk_struct;
  vk::render::Renderpass* vk_renderpass;
  vk::synchro::Semaphore* vk_semaphore;
  vk::render::Swapchain* vk_swapchain;
  vk::pipeline::compute::Pipeline* vk_pipeline;
};

}
