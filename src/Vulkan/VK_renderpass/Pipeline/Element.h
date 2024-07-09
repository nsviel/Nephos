#pragma once

#include <vulkan/vulkan.h>

namespace vk::binding{class Descriptor;}
namespace vk::draw{class Viewport;}
namespace vk::shader{class Shader;}
namespace vk::pipeline{class Data;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}


namespace vk::renderpass{

class Element
{
public:
  //Constructor / Destructor
  Element(vk::Structure* vk_struct);
  ~Element();

public:
  //Main function
  void find_pipeline_element(vk::structure::Pipeline* pipeline);

  //Subfunction
  void find_pipeline_dynamic_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_viewport_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_rasterization_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_multisampling_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_depth_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_blend_attachment_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_blend_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_topology_state(vk::structure::Pipeline* pipeline);

private:
  vk::Structure* vk_struct;
  vk::binding::Descriptor* vk_descriptor;
  vk::shader::Shader* vk_shader;
  vk::pipeline::Data* vk_data;
};

}
