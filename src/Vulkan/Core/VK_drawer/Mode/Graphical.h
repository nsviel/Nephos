#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::structure{class Semaphore;}
namespace vk::presentation{class Swapchain;}
namespace vk::structure{class Command;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Render;}
namespace vk::draw{class Renderer;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::memory{class Transfer;}
namespace sys::timer{class Chrono;}
namespace vk::commandbuffer{class Command_buffer;}
namespace vk::window{class Window;}


namespace vk::draw{

class Graphical
{
public:
  //Constructor / Destructor
  Graphical(vk::Structure* vk_struct);
  ~Graphical();

public:
  //Main function
  void record_rendering(vk::structure::Render& render);
  bool acquire_next_image(vk::structure::Render& render);
  void record_renderpass(vk::structure::Render& render);
  void copy_to_swapchain(vk::structure::Render& render);

  //Subfunction
  void prepare_render(vk::structure::Render& render);
  void prepare_command(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::memory::Transfer* vk_transfer;
  vk::presentation::Swapchain* vk_swapchain;
  sys::timer::Chrono* utl_chrono;
  vk::draw::Renderer* vk_render;
  vk::window::Window* vk_window;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
  vk::commandbuffer::Command_buffer* vk_command;
};

}
