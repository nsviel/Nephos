#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace eng{class Node;}
class VK_engine;
class VK_pipeline;
class VK_viewport;
namespace vk::binding{class Descriptor;}
namespace vk::binding{class VK_uniform;}
class VK_drawing;
namespace eng::render{class Node;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace eng::renderpass{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(eng::render::Node* node_render);
  ~Glyph();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw_scene(vk::structure::Subpass* subpass);
  void cmd_draw_point(vk::structure::Subpass* subpass);
  void cmd_draw_line(vk::structure::Subpass* subpass);

private:
  eng::render::Node* node_render;
  vk::structure::Vulkan* struct_vulkan;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::VK_uniform* vk_uniform;
  VK_drawing* vk_drawing;
  VK_engine* vk_engine;
  VK_pipeline* vk_pipeline;
  VK_viewport* vk_viewport;

  Timer timer;
  float time_renderpass;
};

}
