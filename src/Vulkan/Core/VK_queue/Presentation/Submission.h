#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <thread>

namespace vk::presentation{class Swapchain;}
namespace vk::presentation{class Surface;}
namespace vk{class Structure;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Semaphore;}
namespace vk::window{class Window;}
namespace vk::structure{class Command;}
namespace vk::commandbuffer::structure{class Set;}
namespace vk::draw{class Graphical;}
namespace vk::synchro{class Semaphore;}
namespace vk::gui{class Imgui;}


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
  void submit_rendering(std::vector<std::unique_ptr<vk::structure::Command>>& vec_command, vk::structure::Semaphore& semaphore);
  void submit_presentation(vk::structure::Semaphore& semaphore);
  void next_frame_ID();

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
