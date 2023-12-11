#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>

class ENG_shader;
class Engine;
class Struct_vulkan;
class VK_engine;
class VK_pipeline;
class VK_viewport;
class VK_descriptor;
class VK_uniform;
class VK_drawing;


class RP_scene
{
public:
  //Constructor / Destructor
  RP_scene(Engine* engine);
  ~RP_scene();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(vk::structure::Struct_vk_renderpass* renderpass);

  //Draw function
  void draw_scene(vk::structure::Struct_vk_subpass* subpass);
  void cmd_draw_point(vk::structure::Struct_vk_subpass* subpass);
  void cmd_draw_line(vk::structure::Struct_vk_subpass* subpass);

private:
  ENG_shader* eng_shader;
  Struct_vulkan* struct_vulkan;
  VK_descriptor* vk_descriptor;
  VK_uniform* vk_uniform;
  VK_drawing* vk_drawing;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_viewport* vk_viewport;

  Timer timer;
  float time_renderpass;
};
