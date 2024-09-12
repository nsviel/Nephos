#pragma once

namespace vk{class Structure;}
namespace vk::structure{class Subpass;}


namespace vk::render::onscreen{

class Pipeline
{
public:
  //Constructor / Destructor
  Pipeline(vk::Structure* vk_struct);
  ~Pipeline();

public:
  //Main function
  void add_pipeline_triangle(vk::structure::Subpass* subpass);

private:
  vk::Structure* vk_struct;
};

}
