#ifndef VK_FRAME_H
#define VK_FRAME_H

#include "../Struct/struct_frame.h"
#include "../Struct/struct_renderpass.h"
#include "../Struct/struct_swapchain.h"
#include <Specific/common.h>

class VK_engine;
class VK_struct;
class VK_physical_device;
class VK_image;
class VK_synchronization;
class VK_color;
class VK_framebuffer;
class VK_swapchain;
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
  void create_frame_swapchain(Struct_swapchain* swapchain);
  void clean_frame_swapchain(Struct_swapchain* swapchain);

private:
  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_physical_device* vk_physical_device;
  VK_image* vk_image;
  VK_synchronization* vk_synchronization;
  VK_color* vk_color;
  VK_swapchain* vk_swapchain;
  VK_framebuffer* vk_framebuffer;
  VK_depth* vk_depth;
};

#endif
