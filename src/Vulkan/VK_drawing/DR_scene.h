#ifndef VK_DRAW_SCENE_H
#define VK_DRAW_SCENE_H

#include <VK_struct/struct_frame.h>
#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_command.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;
class VK_command;
class VK_descriptor;
class VK_submit;
class VK_data;
class VK_uniform;
class VK_viewport;
class VK_pipeline;
class VK_drawing;


class DR_scene
{
public:
  //Constructor / Destructor
  DR_scene(VK_engine* vk_engine);
  ~DR_scene();

public:
  //Main functions
  void draw_scene(Struct_renderpass* renderpass);

  //Command function
  void cmd_draw_scene(Struct_renderpass* renderpass);
  void cmd_draw_glyph(Struct_renderpass* renderpass);

private:
  Timer timer;

  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_data* vk_data;
  VK_uniform* vk_uniform;
  VK_viewport* vk_viewport;
  VK_pipeline* vk_pipeline;
  VK_drawing* vk_drawing;
};

#endif
