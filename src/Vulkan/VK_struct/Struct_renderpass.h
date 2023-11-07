#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_pipeline.h>
#include <VK_struct/Struct_viewport.h>
#include <VK_struct/Struct_subpass.h>
#include <ELE_specific/common.h>


struct Struct_renderpass{
  //---------------------------

  //Function
  Struct_pipeline* get_pipeline_byName(string name){
    for(int i=0; i<vec_pipeline.size(); i++){
      if(vec_pipeline[i]->definition.name == name){
        return vec_pipeline[i];
      }
    }
    cout<<"[error] Pipeline by name error -> "+ name +" not found"<<endl;
    return nullptr;
  }

  //Info
  std::string name;
  std::string subpass_trg;

  //Render pass elements
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;
  Struct_framebuffer* framebuffer;

  //Element
  std::vector<Struct_pipeline*> vec_pipeline;
  std::vector<Struct_subpass*> vec_subpass;

  //Synchronization
  VkSemaphore semaphore_wait;
  VkSemaphore semaphore_done;
  VkFence fence;

  //Drawing function
  std::function<void(Struct_renderpass* renderpass)> draw_task;

  //---------------------------
};



#endif
