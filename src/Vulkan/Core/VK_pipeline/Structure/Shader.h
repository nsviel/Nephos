#pragma once

#include <Vulkan/Core/VK_pipeline/Element/Vertex.h>
#include <Vulkan/Core/VK_binding/Structure/Descriptor.h>
#include <Vulkan/Core/VK_binding/Structure/Binding.h>
#include <Utility/Base/Shader/Info.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::pipeline::structure{

struct Shader{
  //---------------------------

  VkShaderModule vs;
  VkShaderModule fs;

  //---------------------------
};

}
