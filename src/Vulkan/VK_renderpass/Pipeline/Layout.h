#pragma once

#include <vulkan/vulkan.h>

namespace vk::binding{class Descriptor;}
namespace vk::draw{class Viewport;}
namespace vk::renderpass{class Shader;}
namespace vk::pipeline{class Data;}
namespace vk::renderpass{class Element;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}


namespace vk::renderpass{

class Layout
{
public:
  //Constructor / Destructor
  Layout(vk::Structure* vk_struct);
  ~Layout();

public:
  //Main function
  void clean_pipeline_struct(vk::structure::Pipeline* pipeline);

  //Pipeline creation
  void create_pipeline_handle(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline);
  void create_pipeline_layout(vk::structure::Pipeline* pipeline);

private:
  vk::Structure* vk_struct;
  vk::binding::Descriptor* vk_descriptor;
  vk::renderpass::Shader* vk_shader;
  vk::pipeline::Data* vk_data;
  vk::renderpass::Element* vk_element;
};

}
