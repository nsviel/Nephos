#pragma once

#include <Utility/Specific/common.h>

namespace vk::image{class Color;}
namespace vk::image{class Depth;}
class VK_image;
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Framebuffer;}
namespace vk::structure{class Frame;}


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(vk::structure::Vulkan* struct_vulkan);
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
  vk::structure::Vulkan* struct_vulkan;
  vk::image::Color* vk_color;
  vk::image::Depth* vk_depth;
  VK_image* vk_image;
};
