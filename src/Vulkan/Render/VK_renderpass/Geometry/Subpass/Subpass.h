#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::render::pipeline{class Factory;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::draw{class Drawer;}
namespace vk::structure{class Subpass;}
namespace utl::base{class Data;}


namespace vk::render::geometry{

class Subpass
{
public:
  //Constructor / Destructor
  Subpass(vk::Structure* vk_struct);
  ~Subpass();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_subpass(vk::structure::Subpass& subpass);

  //Subfunction
  void draw_pipeline_point(vk::structure::Subpass& subpass);
  void draw_pipeline_line(vk::structure::Subpass& subpass);
  void draw_pipeline_triangle(vk::structure::Subpass& subpass);
  void draw_pipeline_dynamic(vk::structure::Subpass& subpass);
  bool check_data(utl::base::Data& data, int topology);

private:
  vk::Structure* vk_struct;
  vk::render::pipeline::Factory* vk_factory;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::descriptor::Uniform* vk_uniform;
  vk::draw::Drawer* vk_drawer;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
};

}
