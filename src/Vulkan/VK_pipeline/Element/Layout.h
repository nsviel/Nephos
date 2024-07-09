#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::structure{class Pipeline;}


namespace vk::pipeline{

class Layout
{
public:
  //Constructor / Destructor
  Layout(vk::Structure* vk_struct);
  ~Layout();

public:
  //Main function
  void clean_pipeline_layout(vk::structure::Pipeline* pipeline);
  void clean_pipeline_handle(vk::structure::Pipeline* pipeline);

  //Pipeline creation

  void create_pipeline_layout(vk::structure::Pipeline* pipeline);

private:
  vk::Structure* vk_struct;
};

}
