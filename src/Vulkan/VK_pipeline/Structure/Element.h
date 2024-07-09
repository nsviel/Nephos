#pragma once

#include <Vulkan/VK_pipeline/Structure/Shader.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Element{
  //---------------------------

  std::vector<VkPipelineShaderStageCreateInfo> shader_stage;
  std::vector<vk::pipeline::structure::Shader> vec_shader;

  std::vector<VkVertexInputBindingDescription> vec_vertex_binding;
  std::vector<VkVertexInputAttributeDescription> vec_vertex_attribut;
  std::vector<VkDynamicState> vec_dynamic_state;

  //---------------------------
};

}
