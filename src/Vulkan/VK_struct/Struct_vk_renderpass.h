#pragma once

#include <VK_struct/Struct_vk_subpass.h>
#include <VK_struct/Namespace.h>
#include <UTL_specific/common.h>


namespace vk::structure{

struct Struct_vk_renderpass{
  //---------------------------

  //Info
  std::string name;
  std::string target;
  std::vector<vk::structure::Struct_vk_subpass*> vec_subpass;

  //Renderpass stuff
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;
  vk::structure::Framebuffer* framebuffer;
  vk::structure::Command command;

  //---------------------------
};

}
