#ifndef VK_DRAW_EDL_H
#define VK_DRAW_EDL_H

#include "../../../Struct/struct_frame.h"
#include "../../../Struct/struct_renderpass.h"
#include "../../../Struct/struct_command.h"
#include "../../../../../common.h"

class Shader_edl;
class VK_engine;
class VK_param;
class VK_command;
class VK_cmd;
class VK_descriptor;
class VK_submit;
class VK_uniform;
class VK_canvas;


class VK_draw_edl
{
public:
  //Constructor / Destructor
  VK_draw_edl(VK_engine* vk_engine);
  ~VK_draw_edl();

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
  Shader_edl* shader_edl;

  VK_canvas* vk_canvas;
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_uniform* vk_uniform;
};

#endif
