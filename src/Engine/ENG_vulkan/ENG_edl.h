#ifndef VK_EDL_RENDERPASS_H
#define VK_EDL_RENDERPASS_H

#include <VK_struct/struct_renderpass.h>
#include <VK_struct/struct_pipeline.h>
#include <ENG_shader/Shader.h>
#include <ELE_specific/common.h>

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


class ENG_edl
{
public:
  //Constructor / Destructor
  ENG_edl(Engine* engine);
  ~ENG_edl();

public:
  //Init functions
  Struct_renderpass* init_renderpass();
  Struct_pipeline* create_pipeline_edl(Struct_renderpass* renderpass);

  //Draw function
  void draw_edl(Struct_renderpass* renderpass);
  void update_descriptor(Struct_renderpass* renderpass);
  void cmd_draw(Struct_renderpass* renderpass);

private:
  Struct_vulkan* struct_vulkan;
  EDL_shader* edl_shader;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_uniform* vk_uniform;
  VK_drawing* vk_drawing;
  VK_renderpass* vk_renderpass;

  Timer timer;
  float time_renderpass;
};

#endif
