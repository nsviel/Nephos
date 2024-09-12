#pragma once

namespace vk{class Structure;}
namespace vk::binding{class Uniform;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}


namespace vk::render::pipeline{

class Topology
{
public:
  //Constructor / Destructor
  Topology(vk::Structure* vk_struct);
  ~Topology();

public:
  //Main function
  void add_pipeline_line(vk::structure::Subpass& subpass);
  void add_pipeline_point(vk::structure::Subpass& subpass);
  void add_pipeline_triangle(vk::structure::Subpass& subpass);

private:
  vk::Structure* vk_struct;
  vk::binding::Uniform* vk_uniform;
};

}
