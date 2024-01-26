#pragma once

#include <Utility/Specific/common.h>

namespace vk::binding{class Descriptor;}
class VK_viewport;
class VK_shader;
namespace vk::data{class Data;}
namespace vk::structure{class Vulkan;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Pipeline;}


class VK_pipeline
{
public:
  //Constructor / Destructor
  VK_pipeline(vk::structure::Vulkan* struct_vulkan);
  ~VK_pipeline();

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

  //Pipeline element
  void find_pipeline_dynamic_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_viewport_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_rasterization_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_multisampling_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_depth_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_blend_attachment_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_blend_state(vk::structure::Pipeline* pipeline);
  void find_pipeline_topology_state(vk::structure::Pipeline* pipeline);

  //Subfunction
  void check_struct_pipeline_input(vk::structure::Pipeline* pipeline);

private:
  vk::structure::Vulkan* struct_vulkan;
  vk::binding::Descriptor* vk_descriptor;
  VK_shader* vk_shader;
  vk::data::Data* vk_data;
};
