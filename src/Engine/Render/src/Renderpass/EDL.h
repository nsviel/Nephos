#pragma once

#include <Utility/Specific/common.h>

namespace vk::main{class Engine;}
namespace vk::renderpass{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class Drawer;}
namespace eng::render{class Node;}
namespace eng::shader{class EDL;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace eng::renderpass{

class EDL
{
public:
  //Constructor / Destructor
  EDL(eng::render::Node* node_render);
  ~EDL();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw_edl(vk::structure::Subpass* subpass);
  void update_binding(vk::structure::Subpass* subpass);
  void draw_canvas(vk::structure::Subpass* subpass);

private:
  eng::shader::EDL* shader_edl;
  vk::main::Engine* vk_engine;
  vk::renderpass::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawing;
};

}
