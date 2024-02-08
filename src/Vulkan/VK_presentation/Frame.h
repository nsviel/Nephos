#pragma once

#include <Utility/Specific/common.h>

namespace vk::image{class Image;}
namespace vk::synchro{class Semaphore;}
namespace vk::synchro{class Fence;}
namespace vk::image{class Color;}
namespace vk::renderpass{class Framebuffer;}
namespace vk::image{class Depth;}
namespace vk::structure{class Vulkan;}


namespace vk::presentation{

class Frame
{
public:
  //Constructor / Destructor
  Frame(vk::structure::Vulkan* struct_vulkan);
  ~Frame();

public:
  //Main function
  void create_frame();
  void clean_frame();

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::synchro::Semaphore* vk_synchronization;
  vk::synchro::Fence* vk_fence;
  vk::renderpass::Framebuffer* vk_framebuffer;
  vk::image::Image* vk_image;
  vk::image::Color* vk_color;
  vk::image::Depth* vk_depth;
};

}
