#pragma once

#include <Vulkan/VK_pipeline/Structure/Definition.h>
#include <Vulkan/VK_pipeline/Structure/Info.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::structure{

struct Pipeline{
  //---------------------------

  VkPipeline pipeline = VK_NULL_HANDLE;
  VkPipelineLayout layout = VK_NULL_HANDLE;

  vk::binding::structure::Binding binding;
  vk::pipeline::structure::Definition definition;
  vk::pipeline::structure::Info info;

  //---------------------------
};

}
