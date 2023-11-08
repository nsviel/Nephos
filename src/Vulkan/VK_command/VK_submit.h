#ifndef VK_SUBMIT_H
#define VK_SUBMIT_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_command.h>
#include <VK_struct/Struct_swapchain.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_surface;
class VK_swapchain;


class VK_submit
{
public:
  //Constructor / Destructor
  VK_submit(VK_engine* vk_engine);
  ~VK_submit();

public:
  //Main functions
  void acquire_next_image(Struct_swapchain* swapchain, VkSemaphore& semaphore, VkFence& fence);
  void set_next_frame_ID(Struct_swapchain* swapchain);

  //Queue submission
  void submit_graphics_command(Struct_command* commands);
  void submit_presentation(Struct_swapchain* swapchain, VkSemaphore& semaphore);

private:
  Struct_vulkan* struct_vulkan;
  VK_surface* vk_surface;
  VK_swapchain* vk_swapchain;
};

#endif
