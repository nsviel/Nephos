#pragma once

namespace vk{class Structure;}
namespace vk::render::topology{class Point;}
namespace vk::render::topology{class Line;}
namespace vk::render::topology{class Triangle;}
namespace vk::render::dynamic{class Point;}


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
  vk::render::topology::Point* vk_point;
  vk::render::topology::Line* vk_line;
  vk::render::topology::Triangle* vk_triangle;
  vk::render::dynamic::Point* vk_dynamic_point;
};

}
