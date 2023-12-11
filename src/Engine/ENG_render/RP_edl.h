#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Namespace.h>
#include <ENG_shader/ENG_shader.h>
#include <UTL_specific/common.h>

class Engine;
class VK_engine;
class VK_pipeline;
class VK_viewport;
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
  void init_renderpass();
  void create_subpass(vk::structure::Struct_vk_renderpass* renderpass);

  //Draw function
  void draw_edl(vk::structure::Struct_vk_subpass* subpass);
  void update_descriptor(vk::structure::Struct_vk_subpass* subpass);
  void draw_command(vk::structure::Struct_vk_subpass* subpass);

private:
  EDL_shader* edl_shader;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_viewport* vk_viewport;
  VK_descriptor* vk_descriptor;
  VK_uniform* vk_uniform;
  VK_drawing* vk_drawing;

  Timer timer;
  float time_renderpass;
};
