#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::geometry::pipeline::topology{class Point;}
namespace vk::pipeline::gfx{class Pipeline;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::pipeline{class Descriptor;}
namespace vk::data{class Vertex;}
namespace vk::structure{class Render;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Object;}
namespace vk::structure{class Descriptor_set;}


namespace vk::geometry::subpass::topology{

class Point
{
public:
  //Constructor / Destructor
  Point(vk::Structure* vk_struct);
  ~Point();

public:
  //Main function
  void create_subpass(vk::structure::Renderpass& renderpass);
  void draw_subpass(std::shared_ptr<vk::structure::Render> render);

private:
  //Subfunction
  void bind_pipeline(std::shared_ptr<vk::structure::Render> render);
  void update_uniform(std::shared_ptr<vk::structure::Render> render);
  void draw_data(std::shared_ptr<vk::structure::Render> render);
  bool check_data(vk::structure::Object& vk_object, int topology);

private:
  vk::Structure* vk_struct;
  vk::geometry::pipeline::topology::Point* vk_point;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::descriptor::Uniform* vk_uniform;
  vk::data::Vertex* vk_drawer;
  vk::pipeline::gfx::Pipeline* vk_pipeline;
  vk::pipeline::Descriptor* vk_descriptor;
};

}
