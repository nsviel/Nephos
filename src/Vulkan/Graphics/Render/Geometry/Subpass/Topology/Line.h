#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::geometry::pipeline::topology{class Line;}
namespace vk::pipeline::gfx{class Pipeline;}
namespace vk::descriptor{class Descriptor_set;}
namespace vk::descriptor{class Uniform;}
namespace vk::pipeline{class Descriptor;}
namespace vk::data{class Vertex;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Render;}
namespace vk::structure{class Subpass;}
namespace vk::structure{class Pipeline;}
namespace vk::structure{class Object;}
namespace vk::structure{class Descriptor_set;}


namespace vk::geometry::subpass::topology{

class Line
{
public:
  //Constructor / Destructor
  Line(vk::Structure* vk_struct);
  ~Line();

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
  vk::geometry::pipeline::topology::Line* vk_line;
  vk::descriptor::Descriptor_set* vk_descriptor_set;
  vk::descriptor::Uniform* vk_uniform;
  vk::data::Vertex* vk_vertex;
  vk::pipeline::gfx::Pipeline* vk_pipeline;
  vk::pipeline::Descriptor* vk_descriptor;
};

}
