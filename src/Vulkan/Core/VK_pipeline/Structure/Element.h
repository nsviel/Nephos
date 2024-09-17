#pragma once

#include <vulkan/vulkan.h>
#include <vector>


namespace vk::pipeline::structure{

struct Element{
  //---------------------------

  std::vector<VkPipelineShaderStageCreateInfo> vec_shader_stage;
  std::vector<VkVertexInputBindingDescription> vec_vertex_binding;
  std::vector<VkVertexInputAttributeDescription> vec_vertex_attribute;
  std::vector<VkDynamicState> vec_dynamic_state;

  VkPipelineVertexInputStateCreateInfo vertex;
  VkPipelineInputAssemblyStateCreateInfo topology;
  VkPipelineDynamicStateCreateInfo dynamic;
  VkPipelineViewportStateCreateInfo viewport;
  VkPipelineRasterizationStateCreateInfo rasterization;
  VkPipelineMultisampleStateCreateInfo multisample;
  VkPipelineColorBlendAttachmentState blend_attachment;
  VkPipelineColorBlendStateCreateInfo blend;
  VkPipelineDepthStencilStateCreateInfo stencil;

  //---------------------------
};

}
