#pragma once

namespace vk{class Structure;}
namespace vk::binding{class Uniform;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::render::offscreen{class Shader;}


namespace vk::render::offscreen{

class Topology
{
public:
  //Constructor / Destructor
  Topology(vk::Structure* vk_struct, vk::render::offscreen::Shader* vk_shader);
  ~Topology();

public:
  //Main function
  void create_pipeline_line(vk::structure::Subpass* subpass);
  void create_pipeline_point(vk::structure::Subpass* subpass);
  void create_pipeline_triangle(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
  vk::binding::Uniform* vk_uniform;
  vk::render::offscreen::Shader* vk_shader;
};

}
