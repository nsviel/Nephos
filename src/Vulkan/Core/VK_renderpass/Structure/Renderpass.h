#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Subpass.h>
#include <Vulkan/Core/VK_renderpass/Structure/Framebuffer.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::structure{

struct Renderpass{
  //---------------------------

  //Info
  std::string name = "";
  float duration = -1;

  //Renderpass stuff
  VkRenderPass handle = VK_NULL_HANDLE;
  VkPipelineStageFlags pipeline_flag = 0;
  vk::structure::Framebuffer framebuffer;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  vk::renderpass::Target target = vk::renderpass::SHADER;
  
  //Subpass description
  std::vector<vk::structure::Subpass*> vec_subpass;
  std::vector<VkSubpassDescription> vec_description;
  std::vector<VkSubpassDependency> vec_dependency;
  std::vector<VkAttachmentDescription> vec_attachment;

  //Attachment
  vk::structure::Attachment depth;
  std::vector<vk::structure::Attachment> vec_color;
  std::vector<vk::structure::Attachment> vec_color_resolve;

  //---------------------------
};

}
