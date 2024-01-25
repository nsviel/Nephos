#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

class VK_presentation;
class VK_render;
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(vk::structure::Vulkan* struct_vulkan);
  ~VK_drawing();

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
  VK_presentation* vk_presentation;
  VK_render* vk_render;

  Timer timer;
};
