#ifndef VK_DRAW_SCENE_H
#define VK_DRAW_SCENE_H

#include <VK_struct/struct_frame.h>
#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_command.h>
#include <ELE_specific/common.h>

class VK_engine;
class struct_vulkan;
class VK_command;
class VK_cmd;
class VK_descriptor;
class VK_submit;
class VK_data;
class VK_uniform;
class VK_camera;


class DR_scene
{
public:
  //Constructor / Destructor
  DR_scene(VK_engine* vk_engine);
  ~DR_scene();

public:
  //Main functions
  void draw_scene(Struct_renderpass* renderpass);

  //Subfunction
  void record_command(Struct_renderpass* renderpass);
  void submit_command(Struct_renderpass* renderpass);

  //Command function
  void cmd_draw_scene(Struct_renderpass* renderpass);
  void cmd_draw_glyph(Struct_renderpass* renderpass);

private:
  Timer timer;

  VK_engine* vk_engine;
  struct_vulkan* vk_struct;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_data* vk_data;
  VK_uniform* vk_uniform;
  VK_camera* vk_camera;
};

#endif
