#ifndef RP_SCENE_H
#define RP_SCENE_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ELE_specific/common.h>

class ENG_shader;
class Engine;
class Struct_vulkan;
class VK_engine;
class VK_pipeline;
class VK_viewport;
class VK_descriptor;
class VK_uniform;
class VK_drawing;
class VK_render;


class RP_scene
{
public:
  //Constructor / Destructor
  RP_scene(Engine* engine);
  ~RP_scene();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(Struct_renderpass* renderpass);

  //Draw function
  void draw_scene(Struct_subpass* subpass);
  void cmd_draw_point(Struct_subpass* subpass);
  void cmd_draw_line(Struct_subpass* subpass);

private:
  ENG_shader* eng_shader;
  Struct_vulkan* struct_vulkan;
  VK_descriptor* vk_descriptor;
  VK_uniform* vk_uniform;
  VK_drawing* vk_drawing;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_viewport* vk_viewport;
  VK_render* vk_render;

  Timer timer;
  float time_renderpass;
};

#endif
