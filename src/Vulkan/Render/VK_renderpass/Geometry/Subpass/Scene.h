#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::render::pipeline{class Factory;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::binding{class Descriptor_set;}
namespace vk::binding{class Uniform;}
namespace vk::draw{class Drawer;}
namespace vk::structure{class Subpass;}
namespace utl::base{class Data;}


namespace vk::render::geometry{

class Scene
{
public:
  //Constructor / Destructor
  Scene(vk::Structure* vk_struct);
  ~Scene();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_subpass(vk::structure::Subpass& subpass);

  //Subfunction
  void cmd_draw_point(vk::structure::Subpass& subpass);
  void cmd_draw_line(vk::structure::Subpass& subpass);
  void cmd_draw_triangle(vk::structure::Subpass& subpass);
  bool check_data(utl::base::Data& data, int typology);

private:
  vk::Structure* vk_struct;
  vk::render::pipeline::Factory* vk_factory;
  vk::binding::Descriptor_set* vk_descriptor_set;
  vk::binding::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawer;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
};

}
