#ifndef VK_EDL_RENDERPASS_H
#define VK_EDL_RENDERPASS_H

#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_pipeline.h>
#include <ENG_shader/ENG_shader.h>
#include <ELE_specific/common.h>

class Engine;
class Struct_vulkan;
class VK_engine;
class VK_pipeline;
class VK_viewport;
class VK_command;
class VK_descriptor;
class VK_uniform;
class VK_drawing;


class RP_edl
{
public:
  //Constructor / Destructor
  RP_edl(Engine* engine);
  ~RP_edl();

public:
  //Init functions
  Struct_renderpass* init_renderpass();
  void create_pipeline_edl(Struct_renderpass* renderpass);

  //Draw function
  void draw_edl(Struct_renderpass* renderpass);
  void update_descriptor(Struct_renderpass* renderpass);
  void draw_command(Struct_renderpass* renderpass);

private:
  Struct_vulkan* struct_vulkan;
  EDL_shader* edl_shader;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_viewport* vk_viewport;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_uniform* vk_uniform;
  VK_drawing* vk_drawing;

  Timer timer;
  float time_renderpass;
};

#endif
