#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::render::edl{class Shader;}
namespace vk::draw{class Drawer;}
namespace vk::postprocess::pipeline{class EDL;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::draw{class Drawer;}
namespace vk::render::edl{class Shader;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Renderpass;}


namespace vk::postprocess::subpass{

class EDL
{
public:
  //Constructor / Destructor
  EDL(vk::Structure* vk_struct);
  ~EDL();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_edl(vk::structure::Subpass& subpass);
  void update_sampler(vk::structure::Subpass& subpass);

  //Subfunction
  void bind_pipeline(vk::structure::Subpass& subpass, vk::structure::Pipeline& pipeline);
  void update_descriptor(vk::structure::Subpass& subpass, vk::structure::Pipeline& pipeline);
  void draw_canvas(vk::structure::Subpass& subpass);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::descriptor::Sampler* vk_sampler;
  vk::draw::Drawer* vk_drawer;
  vk::postprocess::pipeline::EDL* vk_edl;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
};

}
