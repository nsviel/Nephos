#pragma once

#include <Vulkan/VK_drawing/Drawing/Drawer.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::synchro::structure{class Semaphore;}
namespace vk::presentation{class Swapchain;}
namespace vk::structure{class Command;}
namespace vk::structure{class Renderpass;}
namespace vk::memory{class Transfer;}
namespace utl::timer{class Chrono;}


namespace vk::draw{

class Graphical : public vk::draw::Drawer
{
public:
  //Constructor / Destructor
  Graphical(vk::Structure* vk_struct);
  ~Graphical();

public:
  //Main function
  void draw_frame();

  //Subfunction
  bool acquire_image(vk::synchro::structure::Semaphore& semaphore);
  void record_renderpass(std::vector<vk::structure::Command*>& vec_command, vk::synchro::structure::Semaphore& semaphore);
  void copy_to_swapchain(std::vector<vk::structure::Command*>& vec_command, vk::synchro::structure::Semaphore& semaphore);
  void submit_presentation(std::vector<vk::structure::Command*>& vec_command);

private:
  vk::memory::Transfer* vk_transfer;
  vk::presentation::Swapchain* vk_swapchain;
  utl::timer::Chrono* utl_chrono;
};

}
