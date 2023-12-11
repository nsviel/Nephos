#pragma once

#include <VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>
#include <VK_struct/Pipeline.h>


class VK_descriptor;
class VK_viewport;
class VK_shader;
class VK_data;


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
  VK_descriptor* vk_descriptor;
  VK_shader* vk_shader;
  VK_data* vk_data;
};
