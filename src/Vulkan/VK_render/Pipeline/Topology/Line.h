#pragma once

namespace vk{class Structure;}
namespace vk::binding{class Uniform;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}


namespace vk::render::pipeline{

class Line
{
public:
  //Constructor / Destructor
  Line(vk::Structure* vk_struct);
  ~Line();

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
};

}
