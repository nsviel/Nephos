#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/Render/VK_render/Structure/Renderpass.h>
#include <Vulkan/Render/VK_render/Structure/EDL.h>
#include <vulkan/vulkan.h>
#include <vector>


namespace vk::gui{

struct Structure{
  //---------------------------

  VkDescriptorSet descriptor = VK_NULL_HANDLE;

  //---------------------------
};

}
