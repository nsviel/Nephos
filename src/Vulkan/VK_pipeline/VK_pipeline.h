#pragma once

#include <VK_struct/Struct_vk_pipeline.h>
#include <VK_struct/Struct_vk_renderpass.h>
#include <UTL_specific/common.h>

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
  void create_pipeline(Struct_vk_renderpass* renderpass);
  void cmd_bind_pipeline(VkCommandBuffer& command_buffer, Struct_vk_pipeline* pipeline);
  void clean_pipeline(Struct_vk_renderpass* renderpass);
  void clean_pipeline_struct(Struct_vk_pipeline* pipeline);
  void clean_pipeline_shader_module(Struct_vk_pipeline* pipeline);

  //Pipeline creation
  void create_pipeline_struct(Struct_vk_renderpass* renderpass, Struct_vk_pipeline* pipeline);
  void create_pipeline_obj(Struct_vk_renderpass* renderpass, Struct_vk_pipeline* pipeline);
  void create_pipeline_layout(Struct_vk_pipeline* pipeline);

  //Pipeline element
  void find_pipeline_dynamic_state(Struct_vk_pipeline* pipeline);
  void find_pipeline_viewport_state(Struct_vk_pipeline* pipeline);
  void find_pipeline_rasterization_state(Struct_vk_pipeline* pipeline);
  void find_pipeline_multisampling_state(Struct_vk_pipeline* pipeline);
  void find_pipeline_depth_state(Struct_vk_pipeline* pipeline);
  void find_pipeline_blend_attachment_state(Struct_vk_pipeline* pipeline);
  void find_pipeline_blend_state(Struct_vk_pipeline* pipeline);
  void find_pipeline_topology_state(Struct_vk_pipeline* pipeline);

  //Subfunction
  void check_struct_pipeline_input(Struct_vk_pipeline* pipeline);

private:
  Struct_vulkan* struct_vulkan;
  VK_descriptor* vk_descriptor;
  VK_shader* vk_shader;
  VK_data* vk_data;
};
