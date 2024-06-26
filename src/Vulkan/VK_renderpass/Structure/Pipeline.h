#pragma once

#include <Vulkan/VK_binding/Structure/Binding.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


//Binding requirement -> Name, Type size, binding, desriptor type, shader stage
typedef std::vector<std::tuple<std::string, std::size_t, int, VkDescriptorType, VkShaderStageFlagBits>> vec_descriptor_required;

struct Pipeline_definition{
  //---------------------------

  //Info
  std::string name = "";
  std::string topology = "";
  std::string purpose = "";

  utl::shader::Info* shader;
  std::vector<std::string> vec_data_name;
  vec_descriptor_required binding;

  //---------------------------
};
struct Pipeline_info{
  //---------------------------

  VkGraphicsPipelineCreateInfo info = {};

  //Pipeline info elements
  std::vector<VkPipelineShaderStageCreateInfo> shader_stage;
  std::vector<VkDynamicState> dynamic_state_object;
  std::vector<VkVertexInputBindingDescription> data_description;
  std::vector<VkVertexInputAttributeDescription> attribut_description;
  std::vector<std::pair<VkShaderModule, VkShaderModule>> vec_shader_couple;

  VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
  VkPipelineInputAssemblyStateCreateInfo input_assembly = {};
  VkPipelineViewportStateCreateInfo viewport_state = {};
  VkPipelineRasterizationStateCreateInfo rasterizer = {};
  VkPipelineMultisampleStateCreateInfo multisampling = {};
  VkPipelineDepthStencilStateCreateInfo depth_stencil = {};
  VkPipelineColorBlendStateCreateInfo color_blend_info = {};
  VkPipelineColorBlendAttachmentState color_blend_attachment = {};
  VkPipelineDynamicStateCreateInfo dynamic_state = {};

  //---------------------------
};

namespace vk::structure{

struct Pipeline{
  //---------------------------

  VkPipeline pipeline = VK_NULL_HANDLE;
  VkPipelineLayout layout = VK_NULL_HANDLE;

  vk::binding::structure::Binding binding;
  Pipeline_definition definition;
  Pipeline_info info;

  //---------------------------
};

}
