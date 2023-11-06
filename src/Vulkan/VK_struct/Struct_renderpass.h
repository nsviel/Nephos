#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include "Struct_frame.h"
#include "Struct_pipeline.h"
#include "Struct_viewport.h"
#include "Struct_subpass.h"
#include <ELE_specific/common.h>


struct Struct_renderpass{
  //---------------------------

  Struct_pipeline* get_pipeline_byName(string name){
    for(int i=0; i<vec_pipeline.size(); i++){
      if(vec_pipeline[i]->definition.name == name){
        return vec_pipeline[i];
      }
    }
    cout<<"[error] Pipeline by name error -> not found"<<endl;
    return nullptr;
  }

  //Info
  std::string name;
  std::string subpass;

  //Renderpass frame set
  VkImageUsageFlags color_image_usage;
  VkImageLayout color_sampler_layout;
  VkImageUsageFlags depth_image_usage;
  VkImageLayout depth_sampler_layout;
  Struct_frame* get_rendering_frame(){return vec_frame[rendering_frame_ID];}
  uint32_t rendering_frame_ID = 0;
  std::vector<Struct_frame*> vec_frame;

  //Render pass elements
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;

  //Attachment
  std::vector<Struct_pipeline*> vec_pipeline;
  std::vector<Struct_subpass*> vec_subpass;

  VkSemaphore semaphore_wait;
  VkSemaphore semaphore_done;
  VkFence fence;

  std::function<void(Struct_renderpass* renderpass)> draw_task;

  //---------------------------
};



#endif
