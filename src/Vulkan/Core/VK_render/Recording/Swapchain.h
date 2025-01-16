#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::presentation{class Swapchain;}
namespace vk::render{class Renderpass;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::memory{class Transfer;}
namespace sys::timer{class Chrono;}
namespace vk::commandbuffer{class Command_buffer;}
namespace vk::window{class Window;}
namespace vk::gui{class Imgui;}
namespace vk::structure{class Command;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Render;}
namespace vk::structure{class Batch;}
namespace vk::structure{class Semaphore;}


namespace vk::render{

class Swapchain
{
public:
  //Constructor / Destructor
  Swapchain(vk::Structure* vk_struct);
  ~Swapchain();

public:
  //Main function
  bool acquire_swapchain_image(std::shared_ptr<vk::structure::Batch> batch);
  void copy_to_swapchain(std::shared_ptr<vk::structure::Batch> batch);

  //Subfunction
  bool acquire_next_image(std::shared_ptr<vk::structure::Batch> batch);
  void next_frame_ID();

private:
  vk::Structure* vk_struct;
  vk::memory::Transfer* vk_transfer;
  vk::presentation::Swapchain* vk_swapchain;
  sys::timer::Chrono* utl_chrono;
  vk::render::Renderpass* vk_render;
  vk::window::Window* vk_window;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
  vk::commandbuffer::Command_buffer* vk_command;
  vk::gui::Imgui* vk_imgui;
};

}
