#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::render::geometry{class Subpass;}
namespace vk::render::geometry{class Point;}
namespace vk::render::geometry{class Line;}


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
  vk::render::geometry::Subpass* vk_subpass;
  vk::render::geometry::Point* vk_point;
  vk::render::geometry::Line* vk_line;
};

}
