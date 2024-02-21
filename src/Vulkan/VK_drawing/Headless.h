#pragma once

#include <Utility/Specific/common.h>

namespace vk::draw{class Renderer;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}


namespace vk::draw{

class Headless
{
public:
  //Constructor / Destructor
  Headless(vk::structure::Vulkan* struct_vulkan);
  ~Headless();

public:
  //Main functions
  void draw_frame();

  //Draw command
  void cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Object* data);
  void cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object* data);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::draw::Renderer* vk_render;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
};

}
