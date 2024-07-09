#pragma once

#include <vulkan/vulkan.h>

namespace vk::binding{class Descriptor;}
namespace vk::draw{class Viewport;}
namespace vk::pipeline{class Shader;}
namespace vk::pipeline{class Data;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
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
  vk::binding::Descriptor* vk_descriptor;
  vk::pipeline::Shader* vk_shader;
  vk::pipeline::Data* vk_data;
};

}
