#pragma once

#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Element{
  //---------------------------

  //Pipeline info elements
  std::vector<VkPipelineShaderStageCreateInfo> shader_stage;
  std::vector<VkVertexInputBindingDescription> data_description;
  std::vector<VkVertexInputAttributeDescription> attribut_description;
  std::vector<std::pair<VkShaderModule, VkShaderModule>> vec_shader_couple;

  //---------------------------
};

}
