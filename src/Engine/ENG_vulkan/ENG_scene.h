#ifndef RP_SCENE_H
#define RP_SCENE_H

#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_pipeline.h>
#include <ELE_specific/common.h>

class Shader;
class Engine;
class Struct_vulkan;
class VK_engine;
class VK_pipeline;
class VK_subpass;
class VK_viewport;
class VK_command;
class VK_descriptor;
class VK_uniform;
class VK_drawing;
class VK_renderpass;


class ENG_scene
{
public:
  //Constructor / Destructor
  ENG_scene(Engine* engine);
  ~ENG_scene();

public:
  //Init functions
  Struct_renderpass* init_renderpass();
  void create_pipeline_point(Struct_renderpass* renderpass);
  void create_pipeline_line(Struct_renderpass* renderpass);

  //Draw function
  void draw_scene(Struct_renderpass* renderpass);
  void cmd_draw_scene(Struct_renderpass* renderpass);
  void cmd_draw_glyph(Struct_renderpass* renderpass);

private:
  Shader* shaderManager;
  Struct_vulkan* struct_vulkan;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_uniform* vk_uniform;
  VK_drawing* vk_drawing;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
  VK_renderpass* vk_renderpass;

  Timer timer;
  float time_renderpass;
};

#endif
