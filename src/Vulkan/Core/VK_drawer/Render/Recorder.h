#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::structure{class Semaphore;}
namespace vk::presentation{class Swapchain;}
namespace vk::structure{class Command;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Render;}
namespace vk::draw{class Renderpass;}
namespace vk::draw{class Graphical;}
namespace vk::synchro{class Fence;}
namespace vk::memory{class Transfer;}
namespace vk::commandbuffer{class Command_buffer;}
namespace vk::window{class Window;}
namespace vk::synchro{class Semaphore;}
namespace sys::timer{class Chrono;}


namespace vk::draw{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(vk::Structure* vk_struct);
  ~Recorder();

public:
  //Main function
  void record_rendering(vk::structure::Render& render);

  //Subfunction
  void record_all_renderpass(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::memory::Transfer* vk_transfer;
  vk::presentation::Swapchain* vk_swapchain;
  vk::draw::Renderpass* vk_renderpass;
  vk::window::Window* vk_window;
  vk::synchro::Fence* vk_fence;
  vk::commandbuffer::Command_buffer* vk_command;
  vk::draw::Graphical* vk_graphical;
  vk::synchro::Semaphore* vk_semaphore;
  sys::timer::Chrono* utl_chrono;
};

}
