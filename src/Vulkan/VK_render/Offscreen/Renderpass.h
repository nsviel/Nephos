#pragma once

namespace vk{class Structure;}
namespace vk::binding{class Uniform;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::render::offscreen{class Shader;}
namespace vk::render::offscreen{class Drawer;}


namespace vk::render::offscreen{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct, vk::render::offscreen::Shader* vk_shader);
  ~Renderpass();

public:
  //Main function
  void init();

  //Init functions
  void create_renderpass(vk::structure::Renderpass* renderpass);
  void create_subpass(vk::structure::Renderpass* renderpass);
  void create_pipeline_line(vk::structure::Subpass* subpass);
  void create_pipeline_point(vk::structure::Subpass* subpass);
  void create_pipeline_triangle(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
  vk::binding::Uniform* vk_uniform;
  vk::render::offscreen::Shader* vk_shader;
  vk::render::offscreen::Drawer* vk_drawer;
};

}
