#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

class VK_presentation;
namespace vk::draw{class Renderer;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Object;}


namespace vk::draw{

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
  vk::draw::Renderer* vk_render;

  Timer timer;
};

}
