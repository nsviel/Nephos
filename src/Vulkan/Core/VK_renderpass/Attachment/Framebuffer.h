#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::image{class Color;}
namespace vk::image{class Depth;}
namespace vk::image{class Image;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Framebuffer;}
namespace vk::structure{class Frame;}


namespace vk::renderpass{

class Framebuffer
{
public:
  //Constructor / Destructor
  Framebuffer(vk::Structure* vk_struct);
  ~Framebuffer();

public:
  //Main function
  void init();
  void clean();

  //Creation function
  void create_framebuffer(vk::structure::Renderpass& renderpass);
  void clean_framebuffer(vk::structure::Renderpass& renderpass);

  //Subfunction
  void create_framebuffer_image(vk::structure::Framebuffer& framebuffer);
  void create_framebuffer_handle(vk::structure::Renderpass& renderpass, vk::structure::Framebuffer& framebuffer);
  void clean_framebuffer_image(vk::structure::Framebuffer& framebuffer);
  void clean_framebuffer_handle(VkFramebuffer& fbo);

private:
  vk::Structure* vk_struct;
  vk::image::Color* vk_color;
  vk::image::Depth* vk_depth;
  vk::image::Image* vk_image;
};

}
