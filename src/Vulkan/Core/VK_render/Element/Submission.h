#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::presentation{class Swapchain;}
namespace vk::window{class Window;}
namespace vk::structure{class Render;}
namespace vk::synchro{class Fence;}

namespace vk::draw{

class Submission
{
public:
  //Constructor / Destructor
  Submission(vk::Structure* vk_struct);
  ~Submission();

public:
  //Main function
  void submit_rendering(std::shared_ptr<vk::structure::Render> render);

private:
  vk::Structure* vk_struct;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::Window* vk_window;
  vk::synchro::Fence* vk_fence;
};

}
