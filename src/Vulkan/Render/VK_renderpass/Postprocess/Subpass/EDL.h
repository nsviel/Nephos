#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::render::edl{class Shader;}
namespace vk::draw{class Drawer;}
namespace vk::render::pipeline{class Factory;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::draw{class Drawer;}
namespace vk::render::edl{class Shader;}
namespace vk::structure{class Subpass;}


namespace vk::render::edl{

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

  //Subfunction
  void update_binding(vk::structure::Subpass& subpass);
  void draw_canvas(vk::structure::Subpass& subpass);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::descriptor::Sampler* vk_sampler;
  vk::draw::Drawer* vk_drawer;
  vk::render::pipeline::Factory* vk_factory;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
};

}
