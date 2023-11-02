#ifndef VK_EDL_DRAWING_H
#define VK_EDL_DRAWING_H

#include <Vulkan/VK_struct/struct_frame.h>
#include <Vulkan/VK_struct/struct_renderpass.h>
#include <Vulkan/VK_struct/struct_command.h>
#include <Specific/common.h>

class EDL_shader;
class VK_engine;
class VK_struct;
class VK_command;
class VK_cmd;
class VK_descriptor;
class VK_submit;
class VK_uniform;
class VK_canvas;


class DR_edl
{
public:
  //Constructor / Destructor
  DR_edl(VK_engine* vk_engine);
  ~DR_edl();

public:
  //Main functions
  void draw_edl(Struct_renderpass* renderpass);

  //Subfunction
  void update_descriptor(Struct_renderpass* renderpass);
  void record_command(Struct_renderpass* renderpass);
  void submit_command(Struct_renderpass* renderpass);

  //Command function
  void cmd_draw(Struct_renderpass* renderpass);

private:
  Timer timer;
  EDL_shader* edl_shader;

  VK_canvas* vk_canvas;
  VK_engine* vk_engine;
  VK_struct* vk_struct;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_uniform* vk_uniform;
};

#endif
