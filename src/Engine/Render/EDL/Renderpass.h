#pragma once

#include <Utility/Specific/Common.h>

namespace vk::main{class Engine;}
namespace vk::renderpass{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class Drawer;}
namespace eng::render{class Manager;}
namespace rnd::edl{class Shader;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace rnd::edl{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(eng::render::Manager* node_render);
  ~Renderpass();

public:
  //Init functions
  void init_renderpass();
  void create_subpass(vk::structure::Renderpass* renderpass);

  //Draw function
  void draw_edl(vk::structure::Subpass* subpass);
  void update_binding(vk::structure::Subpass* subpass);
  void draw_canvas(vk::structure::Subpass* subpass);

private:
  rnd::edl::Shader* shader_edl;
  vk::main::Engine* vk_engine;
  vk::renderpass::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawer;
};

}
