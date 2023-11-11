#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_command.h>
#include <VK_struct/Struct_entity.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_command;
class VK_submit;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(Struct_vulkan* struct_vulkan);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();

  //Subfunction
  void run_next_image();
  void run_renderpass(Struct_renderpass* renderpass, int i);
  void run_command(Struct_renderpass* renderpass, int i);
  void run_presentation();

  //Draw command
  void cmd_draw_data(Struct_subpass* subpass, Struct_entity* data);
  void cmd_line_with(Struct_subpass* subpass, Struct_entity* data);

private:
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_submit* vk_submit;
  Timer timer;
};

#endif
