#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace eng{class Node;}
namespace vk::main{class Engine;}
namespace vk::renderpass{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class Drawer;}
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
  vk::binding::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawing;
  vk::main::Engine* vk_engine;
  vk::renderpass::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;

  Timer timer;
  float time_renderpass;
};

}
