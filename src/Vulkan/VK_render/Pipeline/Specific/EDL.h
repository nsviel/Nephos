#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::render::edl{class Shader;}
namespace vk::render::edl{class Drawer;}


namespace vk::render::pipeline{

class EDL
{
public:
  //Constructor / Destructor
  EDL(vk::Structure* vk_struct, vk::render::edl::Shader* vk_shader);
  ~EDL();

public:
  //Main function
  void add_pipeline(vk::structure::Subpass& subpass);

  //Subfunction
  void set_pipeline(vk::structure::Pipeline& pipeline);
  void set_shader(vk::structure::Pipeline& pipeline);
  void set_binding(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::binding::Uniform* vk_uniform;
  vk::binding::Sampler* vk_sampler;
  vk::render::edl::Drawer* vk_drawer;
  vk::render::edl::Shader* vk_shader;
};

}
