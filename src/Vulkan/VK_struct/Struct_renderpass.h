#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Renderpass{
  //---------------------------

  //Info
  std::string name = "";
  std::string target = "";

  //Renderpass stuff
  VkRenderPass handle = VK_NULL_HANDLE;
  VkPipelineStageFlags pipeline_flag = 0;
  std::vector<vk::structure::Subpass*> vec_subpass;
  vk::structure::Framebuffer* framebuffer = nullptr;
  vk::structure::Command_buffer* command_buffer = nullptr;

  //---------------------------
};

}
