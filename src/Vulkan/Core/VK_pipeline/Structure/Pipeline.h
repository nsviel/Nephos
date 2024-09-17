#pragma once

#include <Vulkan/Core/VK_pipeline/Structure/Info.h>
#include <Vulkan/Core/VK_pipeline/Structure/Element.h>
#include <Vulkan/Core/VK_pipeline/Structure/Descriptor.h>
#include <vulkan/vulkan.h>


namespace vk::structure{

struct Pipeline{
  //---------------------------

  VkPipeline handle = VK_NULL_HANDLE;
  VkPipelineLayout layout = VK_NULL_HANDLE;

  vk::pipeline::structure::Info info;
  vk::pipeline::structure::Element element;
  vk::pipeline::structure::Descriptor descriptor;

  //---------------------------
};

}