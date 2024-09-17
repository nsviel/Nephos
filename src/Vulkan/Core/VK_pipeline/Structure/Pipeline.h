#pragma once

#include <Vulkan/Core/VK_pipeline/Structure/Info.h>
#include <Vulkan/Core/VK_pipeline/Structure/Component.h>
#include <Vulkan/Core/VK_pipeline/Structure/Descriptor.h>
#include <Vulkan/Core/VK_shader/Structure/Shader.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Pipeline{
  //---------------------------

  VkPipeline handle = VK_NULL_HANDLE;
  VkPipelineLayout layout = VK_NULL_HANDLE;

  vk::pipeline::structure::Info info;
  vk::pipeline::structure::Component component;
  vk::pipeline::structure::Descriptor descriptor;
  vk::shader::structure::Shader shader;

  //---------------------------
};

}
