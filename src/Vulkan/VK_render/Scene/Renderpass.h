#pragma once

namespace vk{class Structure;}
namespace vk::renderpass{class Renderpass;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class Drawer;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Renderpass;}
namespace vk::render::scene{class Shader;}
namespace utl::base{class Data;}


namespace vk::render::scene{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
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

  //Draw function
  void draw_scene(vk::structure::Subpass* subpass);
  bool check_data(utl::base::Data* data, int typology);
  void cmd_draw_point(vk::structure::Subpass* subpass);
  void cmd_draw_line(vk::structure::Subpass* subpass);
  void cmd_draw_triangle(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
  vk::binding::Descriptor* vk_descriptor;
  vk::binding::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawer;
  vk::renderpass::Renderpass* vk_renderpass;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::render::scene::Shader* shader_scene;
};

}
