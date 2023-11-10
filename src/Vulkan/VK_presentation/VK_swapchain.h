#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_engine;
class VK_physical_device;
class VK_depth;
class VK_viewport;
class VK_frame;
class VK_framebuffer;


class VK_swapchain
{
public:
  //Constructor / Destructor
  VK_swapchain(VK_engine* vk_engine);
  ~VK_swapchain();

public:
  //Main function
  void recreate_swapChain();
  void clean_swapchain();

  //Swap chain creation
  void create_swapchain();
  void create_swapchain_surface(VkSwapchainCreateInfoKHR& createInfo);
  void create_swapchain_family(VkSwapchainCreateInfoKHR& createInfo);
  void create_swapchain_presentation(VkSwapchainCreateInfoKHR& createInfo);
  void create_swapchain_image(VkSwapchainKHR swapchain, unsigned int min_image_count);

  //Swap chain parameter
  VkSurfaceFormatKHR swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR swapchain_presentation_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);

private:
  Struct_vulkan* struct_vulkan;
  VK_viewport* vk_viewport;
  VK_physical_device* vk_physical_device;
  VK_depth* vk_depth;
  VK_frame* vk_frame;
  VK_framebuffer* vk_framebuffer;
};

#endif
