#pragma once

namespace vk{class Structure;}
namespace vk::geometry::subpass::topology{class Point;}
namespace vk::geometry::subpass::topology{class Line;}
namespace vk::geometry::subpass::topology{class Triangle;}
namespace vk::geometry::subpass::dynamic{class Point;}


namespace vk::geometry{

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
  vk::geometry::subpass::topology::Point* vk_point;
  vk::geometry::subpass::topology::Line* vk_line;
  vk::geometry::subpass::topology::Triangle* vk_triangle;
  vk::geometry::subpass::dynamic::Point* vk_dynamic_point;
};

}
