#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Renderpass{
  //---------------------------

  //Info
  std::string name;
  std::string target;
  std::vector<vk::structure::Subpass*> vec_subpass;

  //Renderpass stuff
  VkRenderPass renderpass;
  vk::structure::Command_buffer* command_buffer;
  vk::structure::Framebuffer* framebuffer;
  vk::structure::Command command;

  //---------------------------
};

}
