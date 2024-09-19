#pragma once

namespace vk{class Structure;}
namespace vk::geometry::pipeline::topology{class Line;}
namespace vk::geometry::pipeline::topology{class Point;}
namespace vk::geometry::pipeline::topology{class Triangle;}
namespace vk::geometry::pipeline::dynamic{class Point;}
namespace vk::structure{class Subpass;}


namespace vk::render::pipeline{

class Factory
{
public:
  //Constructor / Destructor
  Factory(vk::Structure* vk_struct);
  ~Factory();

public:
  //Main function
  void add_pipeline_line(vk::structure::Subpass& subpass);
  void add_pipeline_point(vk::structure::Subpass& subpass);
  void add_pipeline_triangle(vk::structure::Subpass& subpass);
  void add_pipeline_dynamic_point(vk::structure::Subpass& subpass);

private:
  vk::geometry::pipeline::topology::Line* pipe_line;
  vk::geometry::pipeline::topology::Point* pipe_point;
  vk::geometry::pipeline::topology::Triangle* pipe_triangle;
  vk::geometry::pipeline::dynamic::Point* pipe_dynamic_point;
};

}
