#pragma once

#include <Utility/Specific/common.h>

namespace vk::device{class VK_physical_device;}
class VK_viewport;
class VK_frame;
class VK_framebuffer;
class VK_surface;
namespace vk::structure{class Vulkan;}


class VK_swapchain
{
public:
  //Constructor / Destructor
  VK_swapchain(vk::structure::Vulkan* struct_vulkan);
  ~VK_swapchain();

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
  VK_viewport* vk_viewport;
  vk::device::VK_physical_device* vk_physical_device;
  VK_frame* vk_frame;
  VK_framebuffer* vk_framebuffer;
  VK_surface* vk_surface;
};
