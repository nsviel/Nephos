#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::gfx::render::edl{class Shader;}
namespace vk::data{class Vertex;}
namespace vk::gfx::edl{class Pipeline;}
namespace vk::pipeline::gfx{class Pipeline;}
namespace vk::pipeline{class Descriptor;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::descriptor{class Sampler;}
namespace vk::data{class Vertex;}
namespace vk::gfx::render::edl{class Shader;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Render;}
namespace vk::structure{class Descriptor_set;}


namespace vk::gfx::edl{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(vk::Structure* vk_struct);
  ~Subpass();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_subpass(std::shared_ptr<vk::structure::Render> render);
  void update_sampler(vk::structure::Subpass& subpass);

  //Subfunction
  void bind_pipeline(std::shared_ptr<vk::structure::Render> render);
  void update_uniform(std::shared_ptr<vk::structure::Render> render);
  void update_sampler(std::shared_ptr<vk::structure::Render> render);
  void draw_data(std::shared_ptr<vk::structure::Render> render);

private:
  vk::Structure* vk_struct;
  vk::descriptor::Uniform* vk_uniform;
  vk::descriptor::Sampler* vk_sampler;
  vk::data::Vertex* vk_drawer;
  vk::gfx::edl::Pipeline* vk_edl;
  vk::pipeline::gfx::Pipeline* vk_pipeline;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::pipeline::Descriptor* vk_descriptor;
};

}
