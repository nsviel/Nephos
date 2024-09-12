#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Subpass;}


namespace vk::render::pipeline{

class Canvas
{
public:
  //Constructor / Destructor
  Canvas(vk::Structure* vk_struct);
  ~Canvas();

public:
  //Main function
  void add_pipeline_triangle(vk::structure::Subpass& subpass);

private:
  vk::Structure* vk_struct;
};

}
