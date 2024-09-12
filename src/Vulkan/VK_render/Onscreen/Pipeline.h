#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Subpass;}


namespace vk::render::onscreen{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
  ~Renderpass();

public:
  //Main function
  void add_pipeline_triangle(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
};

}
