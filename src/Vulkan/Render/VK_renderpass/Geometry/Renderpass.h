#pragma once

namespace vk{class Structure;}
namespace vk::subpass::topology{class Point;}
namespace vk::subpass::topology{class Line;}
namespace vk::subpass::topology{class Triangle;}
namespace vk::subpass::dynamic{class Point;}


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
  vk::subpass::topology::Point* vk_point;
  vk::subpass::topology::Line* vk_line;
  vk::subpass::topology::Triangle* vk_triangle;
  vk::subpass::dynamic::Point* vk_dynamic_point;
};

}
