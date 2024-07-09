#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk::binding{class Descriptor;}
namespace vk::draw{class Viewport;}
namespace vk::shader{class Shader;}
namespace vk::pipeline{class Data;}
namespace vk{class Structure;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}


namespace vk::pipeline{

class Object
{
public:
  //Constructor / Destructor
  Object(vk::Structure* vk_struct);
  ~Object();

public:
  //Main function
  void create_pipeline_object(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline);

  //Subfunction
  void info_pipeline_topology(vk::structure::Pipeline* pipeline);
  void find_pipeline_dynamic_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_viewport_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_rasterization_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_multisampling_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_depth_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_blend_attachment_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_blend_state(vk::structure::Pipeline* pipeline);

  void create_pipeline_handle(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline);

private:
  vk::Structure* vk_struct;
  vk::binding::Descriptor* vk_descriptor;
  vk::shader::Shader* vk_shader;
  vk::pipeline::Data* vk_data;


  VkPipelineInputAssemblyStateCreateInfo info_topology;
};

}
