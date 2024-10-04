#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Surface;}
namespace vk::window{class Window;}
namespace vk::commandbuffer::structure{class Set;}
namespace vk::draw{class Recorder;}
namespace vk::draw{class Submission;}
namespace vk::synchro{class Semaphore;}
namespace vk::gui{class Imgui;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Semaphore;}
namespace vk::structure{class Command;}
namespace vk::structure{class Render;}


namespace vk::draw{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(vk::Structure* vk_struct);
  ~Renderer();

public:
  //Main function
  void make_rendering();

private:
  vk::Structure* vk_struct;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::Window* vk_window;
  vk::draw::Recorder* vk_recorder;
  vk::synchro::Semaphore* vk_semaphore;
  vk::draw::Submission* vk_submission;
  vk::gui::Imgui* vk_imgui;
};

}
