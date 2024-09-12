#pragma once

namespace vk{class Structure;}
namespace vk::render::pipeline{class Canvas;}
namespace vk::render::pipeline{class Line;}
namespace vk::render::pipeline{class Point;}
namespace vk::render::pipeline{class Triangle;}
namespace vk::render::pipeline{class EDL;}
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
  void add_pipeline_canvas(vk::structure::Subpass& subpass);
  void add_pipeline_line(vk::structure::Subpass& subpass);
  void add_pipeline_point(vk::structure::Subpass& subpass);
  void add_pipeline_triangle(vk::structure::Subpass& subpass);

private:
  vk::Structure* vk_struct;
  vk::render::pipeline::Canvas* pipe_canvas;
  vk::render::pipeline::Line* pipe_line;
  vk::render::pipeline::Point* pipe_point;
  vk::render::pipeline::Triangle* pipe_triangle;
  vk::render::pipeline::EDL* pipe_edl;
};

}
