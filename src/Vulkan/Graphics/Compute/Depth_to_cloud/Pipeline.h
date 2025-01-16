#pragma once

namespace vk{class Structure;}
namespace vk::descriptor{class Uniform;}
namespace vk::pipeline::compute{class Pipeline;}
namespace vk::texture{class Image;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}


namespace vk::gfx::compute::dtc{

class Pipeline
{
public:
  //Constructor / Destructor
  Pipeline(vk::Structure* vk_struct);
  ~Pipeline();

public:
  //Main function
  void create_pipeline();

  //Subfunction
  void set_pipeline(vk::structure::Pipeline& pipeline);
  void set_shader(vk::structure::Pipeline& pipeline);
  void set_binding(vk::structure::Pipeline& pipeline);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::pipeline::compute::Pipeline* vk_pipeline;
  vk::texture::Image* vk_texture;
};

}
