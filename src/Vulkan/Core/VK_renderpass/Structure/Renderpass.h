#pragma once

#include <Vulkan/Core/VK_renderpass/Structure/Subpass.h>
#include <Vulkan/Core/VK_renderpass/Structure/Framebuffer.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>


namespace vk::structure{

struct Attachment_set{
  //---------------------------

  //Attachment
  std::vector<vk::structure::Attachment> vec_color;
  std::vector<vk::structure::Attachment> vec_color_resolve;
  vk::structure::Attachment depth;

  //Description
  vk::renderpass::Target target = vk::renderpass::SHADER;
  std::vector<VkAttachmentReference> vec_color_ref;
  std::vector<VkAttachmentReference> vec_color_resolve_ref;
  std::vector<VkAttachmentDescription> vec_description;

  //---------------------------
};

struct Subpass_set{
  //---------------------------

  std::vector<VkSubpassDescription> vec_description;
  std::vector<VkSubpassDependency> vec_dependency;

  //---------------------------
};

struct Renderpass{
  //---------------------------

  //Info
  std::string name = "";
  float duration = -1;

  //Renderpass
  VkRenderPass handle = VK_NULL_HANDLE;
  VkPipelineStageFlags pipeline_flag = 0;
  std::shared_ptr<vk::structure::Command_buffer> command_buffer;
  std::vector<vk::structure::Subpass*> vec_subpass;

  //Structure
  vk::structure::Framebuffer framebuffer;
  vk::structure::Subpass_set subpass;
  vk::structure::Attachment_set attachment;

  //---------------------------
};

}
