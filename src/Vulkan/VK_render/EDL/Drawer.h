#pragma once

namespace vk{class Structure;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::draw{class Drawer;}
namespace vk::render::edl{class Shader;}
namespace vk::structure{class Subpass;}


namespace vk::render::edl{

class Drawer
{
public:
  //Constructor / Destructor
  Drawer(vk::Structure* vk_struct, vk::render::edl::Shader* vk_shader);
  ~Drawer();

public:
  //Main function
  void draw_edl(vk::structure::Subpass* subpass);

  //Subfunction
  void update_binding(vk::structure::Subpass* subpass);
  void draw_canvas(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
  vk::render::edl::Shader* vk_shader;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::binding::Descriptor* vk_descriptor;
  vk::draw::Drawer* vk_drawer;
  vk::binding::Uniform* vk_uniform;
  vk::binding::Sampler* vk_sampler;
};

}
