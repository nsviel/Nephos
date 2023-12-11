#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


class VK_presentation;
class VK_render;


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
  void cmd_draw_data(VkCommandBuffer& command_buffer, vk::structure::Entity* data);
  void cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Entity* data);

private:
  vk::structure::Vulkan* struct_vulkan;
  VK_presentation* vk_presentation;
  VK_render* vk_render;

  Timer timer;
};
