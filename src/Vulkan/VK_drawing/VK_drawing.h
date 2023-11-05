#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include <VK_struct/struct_frame.h>
#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_command.h>
#include <VK_struct/struct_data.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class Struct_synchro;
class VK_command;
class VK_descriptor;
class VK_swapchain;
class VK_submit;
class ENG_scene;
class ENG_edl;


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

private:
  Timer timer;

  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  Struct_synchro* struct_synchro;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_swapchain* vk_swapchain;
  ENG_scene* rp_scene;
  ENG_edl* rp_edl;
};

#endif
