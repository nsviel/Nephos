#pragma once

#include <Utility/Specific/common.h>

namespace vk::presentation{class Presentation;}
namespace vk::draw{class Renderer;}
namespace vk::synchro{class Fence;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}


namespace vk::draw{

class Drawer
{
public:
  //Constructor / Destructor
  Drawer(vk::structure::Vulkan* struct_vulkan);
  ~Drawer();

public:
  //Main functions
  void draw_frame();
  void draw_frame_headless();
  void draw_frame_presentation();

  //Draw command
  void cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Object* data);
  void cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object* data);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::presentation::Presentation* vk_presentation;
  vk::draw::Renderer* vk_render;
  vk::synchro::Fence* vk_fence;
};

}
