#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_command.h>
#include <VK_struct/Struct_subpass.h>
#include <UTL_specific/common.h>


struct Struct_renderpass{
  //---------------------------

  //Info
  std::string name;
  std::string target;

  //Renderpass stuff
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;
  Struct_framebuffer* framebuffer;
  Struct_command command;
  std::vector<Struct_subpass*> vec_subpass;

  //---------------------------
};



#endif
