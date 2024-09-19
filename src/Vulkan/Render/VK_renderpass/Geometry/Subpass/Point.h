#pragma once

namespace vk{class Structure;}

namespace vk::render::pipeline{class Factory;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::draw{class Drawer;}



namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Object;}


namespace vk::render::geometry{

class Point
{
public:
  //Constructor / Destructor
  Point(vk::Structure* vk_struct);
  ~Point();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_subpass(vk::structure::Subpass& subpass);

private:
  //Subfunction
  void bind_pipeline(vk::structure::Subpass& subpass, vk::structure::Pipeline& pipeline);
  void bind_descriptor(vk::structure::Subpass& subpass, vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline);
  void draw_data(vk::structure::Object& vk_object, vk::structure::Subpass& subpass);
  bool check_data(vk::structure::Object& vk_object, int topology);

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
