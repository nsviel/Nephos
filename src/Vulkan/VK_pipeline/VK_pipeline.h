#pragma once

#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>
#include <VK_struct/Struct_vk_pipeline.h>

class Struct_vulkan;
class VK_descriptor;
class VK_viewport;
class VK_shader;
class VK_data;


class VK_pipeline
{
public:
  //Constructor / Destructor
  VK_pipeline(Struct_vulkan* struct_vulkan);
  ~VK_pipeline();

public:
  //Main function
  void create_pipeline(vk::structure::Struct_vk_renderpass* renderpass);
  void cmd_bind_pipeline(VkCommandBuffer& command_buffer, vk::structure::Struct_vk_pipeline* pipeline);
  void clean_pipeline(vk::structure::Struct_vk_renderpass* renderpass);
  void clean_pipeline_struct(vk::structure::Struct_vk_pipeline* pipeline);
  void clean_pipeline_shader_module(vk::structure::Struct_vk_pipeline* pipeline);

  //Pipeline creation
  void create_pipeline_struct(vk::structure::Struct_vk_renderpass* renderpass, vk::structure::Struct_vk_pipeline* pipeline);
  void create_pipeline_obj(vk::structure::Struct_vk_renderpass* renderpass, vk::structure::Struct_vk_pipeline* pipeline);
  void create_pipeline_layout(vk::structure::Struct_vk_pipeline* pipeline);

  //Pipeline element
  void find_pipeline_dynamic_state(vk::structure::Struct_vk_pipeline* pipeline);
  void find_pipeline_viewport_state(vk::structure::Struct_vk_pipeline* pipeline);
  void find_pipeline_rasterization_state(vk::structure::Struct_vk_pipeline* pipeline);
  void find_pipeline_multisampling_state(vk::structure::Struct_vk_pipeline* pipeline);
  void find_pipeline_depth_state(vk::structure::Struct_vk_pipeline* pipeline);
  void find_pipeline_blend_attachment_state(vk::structure::Struct_vk_pipeline* pipeline);
  void find_pipeline_blend_state(vk::structure::Struct_vk_pipeline* pipeline);
  void find_pipeline_topology_state(vk::structure::Struct_vk_pipeline* pipeline);

  //Subfunction
  void check_struct_pipeline_input(vk::structure::Struct_vk_pipeline* pipeline);

private:
  Struct_vulkan* struct_vulkan;
  VK_descriptor* vk_descriptor;
  VK_shader* vk_shader;
  VK_data* vk_data;
};
