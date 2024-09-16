#pragma once

namespace vk{class Structure;}
namespace vk::pipeline::topology{class Line;}
namespace vk::pipeline::topology{class Point;}
namespace vk::pipeline::topology{class Triangle;}
namespace vk::pipeline::edl{class EDL;}
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
  void add_pipeline_edl(vk::structure::Subpass& subpass);

private:
  vk::pipeline::topology::Line* pipe_line;
  vk::pipeline::topology::Point* pipe_point;
  vk::pipeline::topology::Triangle* pipe_triangle;
  vk::pipeline::edl::EDL* pipe_edl;
};

}
