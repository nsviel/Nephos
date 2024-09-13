#pragma once

namespace vk{class Structure;}
namespace vk::binding{class Uniform;}
namespace vk::binding{class Sampler;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}


namespace vk::render::pipeline{

class EDL
{
public:
  //Constructor / Destructor
  EDL(vk::Structure* vk_struct);
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
};

}