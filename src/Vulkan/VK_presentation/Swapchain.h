#pragma once

#include <Utility/Specific/common.h>

namespace vk::device{class Physical;}
namespace vk::draw{class Viewport;}
namespace vk::presentation{class Frame;}
class VK_framebuffer;
namespace vk::presentation{class Surface;}
namespace vk::structure{class Vulkan;}


namespace vk::presentation{

class Swapchain
{
public:
  //Constructor / Destructor
  Swapchain(vk::structure::Vulkan* struct_vulkan);
  ~Swapchain();

public:
  //Main function
  void create_swapchain();
  void recreate_swapchain();
  void clean();

  //Swap chain creation
  void create_swapchain_image();
  void create_swapchain_obj();
  void find_swapchain_max_nb_image();
  void find_swapchain_surface_format();
  void find_swapchain_presentation_mode();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::draw::Viewport* vk_viewport;
  vk::device::Physical* dev_physical;
  vk::presentation::Frame* vk_frame;
  VK_framebuffer* vk_framebuffer;
  vk::presentation::Surface* vk_surface;
};

}
