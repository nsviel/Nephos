#pragma once

#include <Vulkan/VK_pipeline/Structure/Info.h>
#include <Vulkan/VK_pipeline/Structure/Element.h>
#include <Vulkan/VK_binding/Structure/Binding.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Pipeline{
  //---------------------------

  VkPipeline handle = VK_NULL_HANDLE;
  VkPipelineLayout layout = VK_NULL_HANDLE;

  vk::pipeline::structure::Info info;
  vk::pipeline::structure::Element element;
  vk::binding::structure::Binding binding;

  //---------------------------
};

}
