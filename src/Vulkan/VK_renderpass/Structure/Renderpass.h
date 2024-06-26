#pragma once

#include <Vulkan/VK_renderpass/Structure/Subpass.h>
#include <Vulkan/VK_renderpass/Structure/Framebuffer.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::structure{

struct Renderpass{
  //---------------------------

  //Info
  std::string name = "";

  //Renderpass stuff
  VkRenderPass handle = VK_NULL_HANDLE;
  VkPipelineStageFlags pipeline_flag = 0;
  std::vector<vk::structure::Subpass*> vec_subpass;
  vk::structure::Framebuffer* framebuffer = nullptr;
  vk::structure::Command_buffer* command_buffer = nullptr;

  //---------------------------
};

}
