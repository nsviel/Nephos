#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include <VK_struct/Struct_frame.h>
#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_renderpass.h>
#include <UTL_specific/common.h>

class VK_color;
class VK_depth;
class VK_image;
class Struct_vulkan;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(Struct_vulkan* struct_vulkan);
  ~VK_framebuffer();

public:
  //Main function
  void create_framebuffers();
  void create_framebuffer(Struct_renderpass* renderpass);
  void clean_framebuffers();
  void clean_framebuffer(Struct_renderpass* renderpass);

  //Subfunction
  void create_framebuffer_renderpass(Struct_renderpass* renderpass, Struct_framebuffer* framebuffer);
  void create_framebuffer_swapchain(Struct_renderpass* renderpass, Struct_frame* frame);
  void clean_framebuffer_obj(VkFramebuffer& fbo);

private:
  Struct_vulkan* struct_vulkan;
  VK_color* vk_color;
  VK_depth* vk_depth;
  VK_image* vk_image;
};

#endif
