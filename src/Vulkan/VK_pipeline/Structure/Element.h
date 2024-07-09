#pragma once

#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Element{
  //---------------------------

  std::vector<std::pair<VkShaderModule, VkShaderModule>> vec_shader_couple;
  std::vector<VkPipelineShaderStageCreateInfo> shader_stage;
  std::vector<VkVertexInputBindingDescription> vertex_binding;
  std::vector<VkVertexInputAttributeDescription> vertex_attribut;
  std::vector<VkDynamicState> vec_dynamic_state;

  //---------------------------
};

}
