#pragma once

#include <VK_struct/Namespace.h>
#include <VK_struct/Struct_vk_pipeline.h>
#include <UTL_specific/common.h>


namespace vk::structure{

struct Struct_vk_subpass{
  //---------------------------

  //Subpass info
  std::string target;
  VkSubpassDescription description;
  VkSubpassDependency dependency;
  VkCommandBuffer command_buffer;

  //Attachment
  vk::structure::Attachment depth;
  std::vector<vk::structure::Attachment> vec_color;
  std::function<void(Struct_vk_subpass* subpass)> draw_task;

  //Pipeline
  std::vector<vk::structure::Struct_vk_pipeline*> vec_pipeline;
  vk::structure::Struct_vk_pipeline* get_pipeline(){
    if(vec_pipeline.size() != 1){
      std::cout<<"[error] several pipeline in subpass"<<std::endl;
      return nullptr;
    }else{
      return vec_pipeline[0];
    }
  }
  vk::structure::Struct_vk_pipeline* get_pipeline_byName(string name){
    for(int i=0; i<vec_pipeline.size(); i++){
      if(vec_pipeline[i]->definition.name == name){
        return vec_pipeline[i];
      }
    }
    std::cout<<"[error] Pipeline by name error -> "+ name +" not found"<<std::endl;
    return nullptr;
  }

  //---------------------------
};

}
