#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_pipeline.h>
#include <VK_struct/Struct_viewport.h>
#include <VK_struct/Struct_subpass.h>
#include <ELE_specific/common.h>


struct Struct_renderpass{
  //---------------------------

  //Info
  std::string name;

  //Renderpass stuff
  VkRenderPass renderpass;
  Struct_framebuffer* framebuffer;
  std::vector<Struct_subpass*> vec_subpass;

  //---------------------------
};



#endif
