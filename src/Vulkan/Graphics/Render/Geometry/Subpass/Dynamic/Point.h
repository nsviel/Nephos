#pragma once

namespace vk{class Structure;}
namespace vk::geometry::pipeline::dynamic{class Point;}
namespace vk::render{class Pipeline;}
namespace vk::draw{class Viewport;}
namespace vk::descriptor{class Sampler;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::data{class Vertex;}
namespace vk::data{class Function;}
namespace vk::descriptor{class Storage;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Object;}


namespace vk::geometry::subpass::dynamic{

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
  void update_uniform(vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline);
  void update_sampler(vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline, vk::structure::Subpass& subpass);
  void draw_data(vk::structure::Object& vk_object, vk::structure::Pipeline& pipeline, vk::structure::Subpass& subpass);
  bool check_data(vk::structure::Object& vk_object, int topology);

private:
  vk::Structure* vk_struct;
  vk::geometry::pipeline::dynamic::Point* vk_point;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::descriptor::Uniform* vk_uniform;
  vk::data::Vertex* vk_drawer;
  vk::render::Pipeline* vk_pipeline;
  vk::draw::Viewport* vk_viewport;
  vk::descriptor::Sampler* vk_sampler;
  vk::descriptor::Storage* vk_storage;
  vk::data::Function* vk_data;
};

}
