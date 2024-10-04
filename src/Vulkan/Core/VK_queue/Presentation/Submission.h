#pragma once

namespace vk{class Structure;}
namespace vk::presentation{class Swapchain;}
namespace vk::structure{class Render;}
namespace vk::window{class Window;}


namespace vk::queue::presentation{

class Submission
{
public:
  //Constructor / Destructor
  Submission(vk::Structure* vk_struct);
  ~Submission();

public:
  //Main function
  void submit_presentation(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::Window* vk_window;
};

}
