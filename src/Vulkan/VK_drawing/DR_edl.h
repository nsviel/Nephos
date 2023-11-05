#ifndef VK_EDL_DRAWING_H
#define VK_EDL_DRAWING_H

#include <VK_struct/struct_frame.h>
#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_command.h>
#include <ELE_specific/common.h>

class EDL_shader;
class VK_engine;
class Struct_vulkan;
class VK_command;
class VK_descriptor;
class VK_submit;
class VK_uniform;
class VK_canvas;
class VK_viewport;
class VK_pipeline;
class VK_drawing;


class DR_edl
{
public:
  //Constructor / Destructor
  DR_edl(VK_engine* vk_engine);
  ~DR_edl();

public:
  //Main functions
  void draw_edl(Struct_renderpass* renderpass);

  //Command function
  void cmd_draw(Struct_renderpass* renderpass);

private:
  Timer timer;
  EDL_shader* edl_shader;

  VK_canvas* vk_canvas;
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_uniform* vk_uniform;
  VK_viewport* vk_viewport;
  VK_pipeline* vk_pipeline;
  VK_drawing* vk_drawing;
};

#endif
