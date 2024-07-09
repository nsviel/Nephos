#pragma once

#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Info{
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

}
