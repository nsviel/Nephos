#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::presentation{class Swapchain;}
namespace vk::window{class Window;}
namespace vk::structure{class Render;}


namespace vk::draw{

class Submission
{
public:
  //Constructor / Destructor
  Submission(vk::Structure* vk_struct);
  ~Submission();

public:
  //Main function
  void submit_rendering(vk::structure::Render& render);
  void submit_presentation(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::Window* vk_window;
};

}
