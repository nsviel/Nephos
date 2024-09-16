#pragma once

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}


namespace vk::pipeline::topology{

class Triangle
{
public:
  //Constructor / Destructor
  Triangle(vk::Structure* vk_struct);
  ~Triangle();

public:
  //Main function
  void add_pipeline(vk::structure::Subpass& subpass);

  //Subfunction
  void set_pipeline(vk::structure::Pipeline& pipeline);
  void set_shader(vk::structure::Pipeline& pipeline);
  void set_binding(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
};

}
