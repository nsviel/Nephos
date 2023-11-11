#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_physical_device;
class VK_viewport;
class VK_frame;
class VK_framebuffer;


class VK_swapchain
{
public:
  //Constructor / Destructor
  VK_swapchain(Struct_vulkan* struct_vulkan);
  ~VK_swapchain();

public:
  //Main function
  void recreate_swapChain();
  void clean_swapchain();

  //Swap chain creation
  void create_swapchain();
  void create_swapchain_surface(VkSwapchainCreateInfoKHR& create_info);
  void create_swapchain_family(VkSwapchainCreateInfoKHR& create_info);
  void create_swapchain_presentation(VkSwapchainCreateInfoKHR& create_info);
  void create_swapchain_image(VkSwapchainKHR swapchain, unsigned int min_image_count);

  //Swap chain parameter
  void find_swapchain_surface_format();
  void find_swapchain_presentation_mode();

private:
  Struct_vulkan* struct_vulkan;
  VK_viewport* vk_viewport;
  VK_physical_device* vk_physical_device;
  VK_frame* vk_frame;
  VK_framebuffer* vk_framebuffer;
};

#endif
