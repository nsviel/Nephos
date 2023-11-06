#ifndef VK_FRAME_H
#define VK_FRAME_H

#include "../VK_struct/Struct_framebuffer.h"
#include "../VK_struct/Struct_renderpass.h"
#include "../VK_struct/Struct_swapchain.h"
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_physical_device;
class VK_image;
class VK_synchronization;
class VK_color;
class VK_framebuffer;
class VK_depth;


class VK_frame
{
public:
  //Constructor / Destructor
  VK_frame(VK_engine* vk_engine);
  ~VK_frame();

public:
  //Renderpass frame
  void create_frame_renderpass(Struct_renderpass* renderpass);
  void clean_frame_renderpass(Struct_renderpass* renderpass);

  //Swapchain frame
  void create_frame_swapchain();
  void clean_frame_swapchain();

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_physical_device* vk_physical_device;
  VK_image* vk_image;
  VK_synchronization* vk_synchronization;
  VK_color* vk_color;
  VK_framebuffer* vk_framebuffer;
  VK_depth* vk_depth;
};

#endif
