#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_physical_device;
class VK_viewport;
class VK_frame;
class VK_framebuffer;
class VK_surface;


class VK_swapchain
{
public:
  //Constructor / Destructor
  VK_swapchain(Struct_vulkan* struct_vulkan);
  ~VK_swapchain();

public:
  //Main function
  void create_swapchain();
  void recreate_swapChain();
  void clean_swapchain();

  //Swap chain creation
  void create_swapchain_image();
  void create_swapchain_obj();
  void find_swapchain_max_nb_image();
  void find_swapchain_surface_format();
  void find_swapchain_presentation_mode();

  //Image acquisition
  void acquire_next_image(VkSemaphore& semaphore, VkFence& fence);
  void submit_presentation(VkSemaphore& semaphore);
  void set_next_frame_ID();

private:
  Struct_vulkan* struct_vulkan;
  VK_viewport* vk_viewport;
  VK_physical_device* vk_physical_device;
  VK_frame* vk_frame;
  VK_framebuffer* vk_framebuffer;
  VK_surface* vk_surface;
};

#endif
