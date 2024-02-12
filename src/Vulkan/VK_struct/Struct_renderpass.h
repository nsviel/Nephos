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
  vk::structure::Command_buffer* command_buffer;

  //Renderpass stuff
  VkRenderPass renderpass;
  vk::structure::Framebuffer* framebuffer;


  //A VIRER
  vk::structure::Command command;

  //---------------------------
};

}
