#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <thread>

namespace vk{class Structure;}
namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Surface;}
namespace vk::window{class Window;}
namespace vk::commandbuffer::structure{class Set;}
namespace vk::draw{class Graphical;}
namespace vk::synchro{class Semaphore;}
namespace vk::gui{class Imgui;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Semaphore;}
namespace vk::structure{class Command;}
namespace vk::structure{class Render;}


namespace vk::queue::presentation{

class Submission
{
public:
  //Constructor / Destructor
  Submission(vk::Structure* vk_struct);
  ~Submission();

public:
  //Main function
  void make_rendering();

  //Subfunction
  void submit_rendering(vk::structure::Render& render);
  void submit_presentation(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::presentation::Surface* vk_surface;
  vk::presentation::Swapchain* vk_swapchain;
  vk::window::Window* vk_window;
  vk::draw::Graphical* vk_drawer;
  vk::synchro::Semaphore* vk_semaphore;
  vk::gui::Imgui* vk_imgui;
};

}
