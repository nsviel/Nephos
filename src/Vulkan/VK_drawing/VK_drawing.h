#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include <VK_struct/struct_frame.h>
#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_command.h>
#include <VK_struct/struct_data.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_command;
class VK_descriptor;
class VK_submit;
class DR_scene;
class DR_edl;
class DR_ui;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(VK_engine* vk_engine);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();
  void cmd_draw_data(Struct_renderpass* renderpass, Struct_data* data);
  void cmd_line_with(Struct_renderpass* renderpass, Struct_data* data);

  inline DR_ui* get_ui_drawing(){return dr_ui;}

private:
  Timer timer;

  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  DR_ui* dr_ui;
  DR_scene* dr_scene;
  DR_edl* dr_edl;
};

#endif
