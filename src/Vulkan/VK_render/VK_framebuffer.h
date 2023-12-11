#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Namespace.h>
#include <VK_struct/Frame.h>
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
  void create_framebuffer(vk::structure::Renderpass* renderpass);
  void clean_framebuffers();
  void clean_framebuffer(vk::structure::Renderpass* renderpass);

  //Subfunction
  void create_framebuffer_renderpass(vk::structure::Renderpass* renderpass, vk::structure::Framebuffer* framebuffer);
  void create_framebuffer_swapchain(vk::structure::Renderpass* renderpass, vk::structure::Frame* frame);
  void clean_framebuffer_obj(VkFramebuffer& fbo);

private:
  Struct_vulkan* struct_vulkan;
  VK_color* vk_color;
  VK_depth* vk_depth;
  VK_image* vk_image;
};
