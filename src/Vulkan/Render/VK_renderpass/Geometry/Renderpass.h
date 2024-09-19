#pragma once

namespace vk{class Structure;}
namespace vk::render::geometry{class Point;}
namespace vk::render::geometry{class Line;}
namespace vk::render::geometry{class Triangle;}


namespace vk::render::geometry{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
  ~Renderpass();

public:
  //Main function
  void init();

private:
  vk::Structure* vk_struct;
  vk::render::geometry::Point* vk_point;
  vk::render::geometry::Line* vk_line;
  vk::render::geometry::Triangle* vk_triangle;
};

}
