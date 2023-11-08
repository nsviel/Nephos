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
  std::string subpass_trg;

  //Drawing stuff
  std::vector<Struct_subpass*> vec_subpass;
  std::function<void(Struct_renderpass* renderpass)> draw_task;
  Struct_framebuffer* framebuffer;

  //Renderpass stuff
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;
  VkSemaphore semaphore_wait;
  VkSemaphore semaphore_done;
  VkFence fence;

  //---------------------------
};



#endif
