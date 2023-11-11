#ifndef VK_FRAME_H
#define VK_FRAME_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_swapchain.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_image;
class VK_synchronization;
class VK_color;
class VK_framebuffer;
class VK_depth;


class VK_frame
{
public:
  //Constructor / Destructor
  VK_frame(Struct_vulkan* struct_vulkan);
  ~VK_frame();

public:
  //Main function
  void create_frame();
  void clean_frame();

private:
  Struct_vulkan* struct_vulkan;
  VK_synchronization* vk_synchronization;
  VK_framebuffer* vk_framebuffer;
  VK_image* vk_image;
  VK_color* vk_color;
  VK_depth* vk_depth;
};

#endif
