#ifndef STRUCT_VK_RENDERPASS_H
#define STRUCT_VK_RENDERPASS_H

#include <VK_struct/Struct_vk_framebuffer.h>
#include <VK_struct/Struct_vk_command.h>
#include <VK_struct/Struct_vk_subpass.h>
#include <UTL_specific/common.h>


struct Struct_vk_renderpass{
  //---------------------------

  //Info
  std::string name;
  std::string target;
  std::vector<Struct_vk_subpass*> vec_subpass;

  //Renderpass stuff
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;
  Struct_vk_framebuffer* framebuffer;
  Struct_vk_command command;

  //---------------------------
};



#endif
