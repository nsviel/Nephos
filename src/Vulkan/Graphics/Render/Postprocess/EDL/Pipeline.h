#pragma once

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::pipeline::gfx{class Pipeline;}


namespace vk::gfx::edl{

class Pipeline
{
public:
  //Constructor / Destructor
  Pipeline(vk::Structure* vk_struct);
  ~Pipeline();

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
  vk::descriptor::Sampler* vk_sampler;
  vk::pipeline::gfx::Pipeline* vk_pipeline;
};

}
