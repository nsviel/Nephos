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

class Pipeline
{
public:
  //Constructor / Destructor
  Pipeline(vk::Structure* vk_struct);
  ~Pipeline();

public:
  //Main function
  void create_pipeline(vk::structure::Renderpass* renderpass);
  void cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Pipeline* pipeline);
  void clean_pipeline(vk::structure::Renderpass* renderpass);
  void clean_pipeline_struct(vk::structure::Pipeline* pipeline);
  void clean_pipeline_shader_module(vk::structure::Pipeline* pipeline);

  //Pipeline creation
  void create_pipeline_struct(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline);
  void create_pipeline_obj(vk::structure::Renderpass* renderpass, vk::structure::Pipeline* pipeline);
  void create_pipeline_layout(vk::structure::Pipeline* pipeline);

private:
  vk::Structure* vk_struct;
  vk::binding::Descriptor* vk_descriptor;
  vk::renderpass::Shader* vk_shader;
  vk::pipeline::Data* vk_data;
  vk::renderpass::Element* vk_element;
};

}
