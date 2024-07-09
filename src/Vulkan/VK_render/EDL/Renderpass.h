#pragma once

namespace vk::renderpass{class Renderpass;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::draw{class Drawer;}
namespace vk::render::edl{class Shader;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk{class Structure;}
namespace vk::render::edl{class Shader;}
namespace vk::render::edl{class Drawer;}


namespace vk::render::edl{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
  ~Renderpass();

public:
  //Main function
  void init();

  //Init functions
  void create_renderpass(vk::structure::Renderpass* renderpass);
  void create_subpass(vk::structure::Renderpass* renderpass);
  void create_pipeline_edl(vk::structure::Subpass* subpass);

  //Draw function
  void draw_edl(vk::structure::Subpass* subpass);
  void update_binding(vk::structure::Subpass* subpass);
  void draw_canvas(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
  vk::render::edl::Shader* shader_edl;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::binding::Descriptor* vk_descriptor;
  vk::draw::Drawer* vk_drawer;
  vk::binding::Uniform* vk_uniform;
  vk::binding::Sampler* vk_sampler;
  vk::render::edl::Drawer* vk_edl_drawer;
};

}
