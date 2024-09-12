#pragma once

#include <Vulkan/VK_renderpass/Structure/Renderpass.h>
#include <Vulkan/VK_render/Structure/Renderpass.h>
#include <Vulkan/VK_render/Structure/EDL.h>
#include <vulkan/vulkan.h>
#include <vector>


namespace vk::render::structure{

struct Render{
  //---------------------------

  vk::render::structure::EDL edl;

  //Af outre dans swapchina/ presentation
  VkFormat required_image_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_B8G8R8A8_SRGB
  VkDescriptorSet descriptor = VK_NULL_HANDLE;
  VkViewport viewport = {};
  VkRect2D scissor = {};

  //---------------------------
};

}
