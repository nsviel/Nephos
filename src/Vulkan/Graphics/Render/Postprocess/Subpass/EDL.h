#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::render::edl{class Shader;}
namespace vk::data{class Vertex;}
namespace vk::postprocess::pipeline{class EDL;}
namespace vk::render{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::pipeline{class Descriptor;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::data{class Vertex;}
namespace vk::render::edl{class Shader;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Render;}
namespace vk::structure{class Descriptor_set;}


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
  void draw_subpass(vk::structure::Render& render);
  void update_sampler(vk::structure::Subpass& subpass);

  //Subfunction
  void bind_pipeline(vk::structure::Render& render);
  void update_uniform(vk::structure::Render& render);
  void update_sampler(vk::structure::Render& render);
  void draw_data(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::descriptor::Sampler* vk_sampler;
  vk::data::Vertex* vk_drawer;
  vk::postprocess::pipeline::EDL* vk_edl;
  vk::render::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::pipeline::Descriptor* vk_descriptor;
};

}
