#pragma once

#include <VK_struct/VK_typedef.h>
#include <VK_struct/Struct_vk_binding.h>
#include <ENG_shader/Base/BASE_shader.h>
#include <UTL_specific/common.h>


//Binding requirement -> Name, Type size, binding, desriptor type, shader stage
typedef std::vector<std::tuple<std::string, std::size_t, int, VkDescriptorType, VkShaderStageFlagBits>> vec_descriptor_required;

struct Struct_vk_pipeline_definition{
  //---------------------------

  //Info
  std::string name = "";
  std::string topology = "";
  std::string purpose = "";

  Shader_info* shader;
  std::vector<std::string> vec_data_name;
  vec_descriptor_required binding;

  //---------------------------
};
struct Struct_vk_pipeline_info{
  //---------------------------

  VkGraphicsPipelineCreateInfo info;

  //Pipeline info elements
  std::vector<VkPipelineShaderStageCreateInfo> shader_stage;
  std::vector<VkDynamicState> dynamic_state_object;
  std::vector<VkVertexInputBindingDescription> data_description;
  std::vector<VkVertexInputAttributeDescription> attribut_description;
  std::vector<std::pair<VkShaderModule, VkShaderModule>> vec_shader_couple;

  VkPipelineVertexInputStateCreateInfo vertex_input_info;
  VkPipelineInputAssemblyStateCreateInfo input_assembly;
  VkPipelineViewportStateCreateInfo viewport_state;
  VkPipelineRasterizationStateCreateInfo rasterizer;
  VkPipelineMultisampleStateCreateInfo multisampling;
  VkPipelineDepthStencilStateCreateInfo depth_stencil;
  VkPipelineColorBlendStateCreateInfo color_blend_info;
  VkPipelineColorBlendAttachmentState color_blend_attachment;
  VkPipelineDynamicStateCreateInfo dynamic_state;

  //---------------------------
};

namespace vk::structure{

struct Struct_vk_pipeline{
  //---------------------------

  VkPipeline pipeline;
  VkPipelineLayout layout;

  Struct_vk_binding binding;
  Struct_vk_pipeline_definition definition;
  Struct_vk_pipeline_info info;

  //---------------------------
};

}
