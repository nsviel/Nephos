#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::render::edl{class Shader;}
namespace vk::draw{class Drawer;}
namespace vk::render::pipeline{class Factory;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::draw{class Drawer;}
namespace vk::render::edl{class Shader;}
namespace vk::structure{class Subpass;}


namespace vk::render::offscreen{

class EDL
{
public:
  //Constructor / Destructor
  EDL(vk::Structure* vk_struct);
  ~EDL();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_edl(vk::structure::Subpass& subpass);

  //Subfunction
  void update_binding(vk::structure::Subpass& subpass);
  void draw_canvas(vk::structure::Subpass& subpass);

private:
  vk::Structure* vk_struct;
  vk::binding::Uniform* vk_uniform;
  vk::binding::Sampler* vk_sampler;
  vk::draw::Drawer* vk_drawer;
  vk::render::pipeline::Factory* vk_factory;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::binding::Descriptor* vk_descriptor;
};

}
