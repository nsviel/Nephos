#pragma once

#include <VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


class VK_physical_device;
class VK_viewport;
class VK_frame;
class VK_framebuffer;
class VK_surface;


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
  void clean_swapchain();

  //Swap chain creation
  void create_swapchain_image();
  void create_swapchain_obj();
  void find_swapchain_max_nb_image();
  void find_swapchain_surface_format();
  void find_swapchain_presentation_mode();

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_viewport* vk_viewport;
  VK_physical_device* vk_physical_device;
  VK_frame* vk_frame;
  VK_framebuffer* vk_framebuffer;
  VK_surface* vk_surface;
};
