#pragma once

#include <Vulkan/VK_struct/Subpass.h>
#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/UTL_specific/common.h>


namespace vk::structure{

struct Renderpass{
  //---------------------------

  //Info
  std::string name;
  std::string target;
  std::vector<vk::structure::Subpass*> vec_subpass;

  //Renderpass stuff
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;
  vk::structure::Framebuffer* framebuffer;
  vk::structure::Command command;

  //---------------------------
};

}
