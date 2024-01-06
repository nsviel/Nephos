#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Shader/Namespace.h>
#include <Utility/Function/Timer/fct_timer.h>

class Engine;
class VK_engine;
class VK_pipeline;
class VK_viewport;
class VK_descriptor;
class VK_uniform;
class VK_drawing;


class RP_glyph
{
public:
  //Constructor / Destructor
  RP_glyph(Engine* engine);
  ~RP_glyph();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw_scene(vk::structure::Subpass* subpass);
  void cmd_draw_point(vk::structure::Subpass* subpass);
  void cmd_draw_line(vk::structure::Subpass* subpass);

private:
  eng::shader::Shader* eng_shader;
  vk::structure::Vulkan* struct_vulkan;
  VK_descriptor* vk_descriptor;
  VK_uniform* vk_uniform;
  VK_drawing* vk_drawing;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_viewport* vk_viewport;

  Timer timer;
  float time_renderpass;
};
