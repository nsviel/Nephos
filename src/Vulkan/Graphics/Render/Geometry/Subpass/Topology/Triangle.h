#pragma once

namespace vk{class Structure;}

namespace vk::geometry::pipeline::topology{class Triangle;}
namespace vk::pipeline{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::data{class Vertex;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Object;}


namespace vk::geometry::subpass::topology{

class Triangle
{
public:
  //Constructor / Destructor
  Triangle(vk::Structure* vk_struct);
  ~Triangle();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_subpass(vk::structure::Subpass& subpass);

private:
  //Subfunction
  void bind_pipeline(vk::structure::Subpass& subpass, vk::structure::Pipeline& pipeline);
  void update_uniform(vk::structure::Subpass& subpass, vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline);
  void draw_data(vk::structure::Object& vk_object, vk::structure::Subpass& subpass);
  bool check_data(vk::structure::Object& vk_object, int topology);

private:
  vk::Structure* vk_struct;
  vk::geometry::pipeline::topology::Triangle* vk_triangle;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::descriptor::Uniform* vk_uniform;
  vk::data::Vertex* vk_drawer;
  vk::pipeline::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
};

}