#pragma once

#include <memory>
#include <vector>

namespace vk{class Structure;}
namespace vk::synchro::structure{class Semaphore;}
namespace vk::presentation{class Swapchain;}
namespace vk::structure{class Command;}
namespace vk::structure{class Renderpass;}
namespace vk::draw{class Renderer;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::memory{class Transfer;}
namespace sys::timer{class Chrono;}



namespace vk::draw{

class Graphical
{
public:
  //Constructor / Destructor
  Graphical(vk::Structure* vk_struct);
  ~Graphical();

public:
  //Main function
  void draw_frame();

  //Subfunction
  void record_renderpass(std::vector<std::unique_ptr<vk::structure::Command>>& vec_command, vk::synchro::structure::Semaphore& semaphore);
  void copy_to_swapchain(std::vector<std::unique_ptr<vk::structure::Command>>& vec_command, vk::synchro::structure::Semaphore& semaphore);

private:
  vk::Structure* vk_struct;
  vk::memory::Transfer* vk_transfer;
  vk::presentation::Swapchain* vk_swapchain;
  sys::timer::Chrono* utl_chrono;
  vk::draw::Renderer* vk_render;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
};

}
