#pragma once

#include <Utility/Specific/Common.h>

namespace vk::image{class Color;}
namespace vk::image{class Depth;}
namespace vk::image{class Image;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Framebuffer;}
namespace vk::structure{class Frame;}


namespace vk::renderpass{

class Framebuffer
{
public:
  //Constructor / Destructor
  Framebuffer(vk::structure::Vulkan* vk_struct);
  ~Framebuffer();

public:
  //Main function
  void create_framebuffers();
  void create_framebuffer(vk::structure::Renderpass* renderpass);
  void clean_framebuffers();
  void clean_framebuffer(vk::structure::Renderpass* renderpass);

  //Subfunction
  void create_framebuffer_handle(vk::structure::Renderpass* renderpass, vk::structure::Framebuffer* framebuffer);
  void create_framebuffer_swapchain(vk::structure::Renderpass* renderpass, vk::structure::Frame* frame);
  void clean_framebuffer_handle(VkFramebuffer& fbo);

private:
  vk::structure::Vulkan* vk_struct;
  vk::image::Color* vk_color;
  vk::image::Depth* vk_depth;
  vk::image::Image* vk_image;
};

}
