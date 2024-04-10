#pragma once

#include <Utility/Specific/Common.h>

namespace vk::main{class Engine;}
namespace vk::renderpass{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class Drawer;}
namespace vk::render::edl{class Shader;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Vulkan;}
namespace vk::render::edl{class Shader;}


namespace vk::render::edl{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::structure::Vulkan* vk_struct);
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
  vk::structure::Vulkan* vk_struct;
  vk::render::edl::Shader* shader_edl;
  vk::main::Engine* vk_engine;
  vk::renderpass::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawer;
};

}
