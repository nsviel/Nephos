#pragma once

#include <Vulkan/VK_struct/Namespace.h>
#include <Utility/Specific/common.h>


namespace vk::structure{

struct Subpass{
  //---------------------------

  //Subpass info
  std::string target;
  VkSubpassDescription description;
  VkSubpassDependency dependency;
  vk::structure::Command_buffer command_buffer;

  //Attachment
  vk::structure::Attachment depth;
  std::vector<vk::structure::Attachment> vec_color;
  std::vector<vk::structure::Attachment> vec_color_resolve;
  std::function<void(Subpass* subpass)> draw_task;

  //Pipeline
  std::vector<vk::structure::Pipeline*> vec_pipeline;
  vk::structure::Pipeline* get_pipeline(){
    if(vec_pipeline.size() != 1){
      std::cout<<"[error] several pipeline in subpass"<<std::endl;
      return nullptr;
    }else{
      return vec_pipeline[0];
    }
  }
  vk::structure::Pipeline* get_pipeline_byName(string name){
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
