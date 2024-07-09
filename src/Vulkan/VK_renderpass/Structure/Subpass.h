#pragma once

#include <Vulkan/VK_renderpass/Renderpass/Subpass.h>
#include <Vulkan/VK_pipeline/Structure/Pipeline.h>
#include <Vulkan/VK_renderpass/Structure/Attachment.h>
#include <vulkan/vulkan.h>
#include <functional>
#include <iostream>
#include <vector>
#include <string>


namespace vk::structure{

struct Subpass{
  //---------------------------

  vk::structure::Pipeline* get_pipeline(){
    if(vec_pipeline.size() != 1){
      std::cout<<"[error] several pipeline in subpass"<<std::endl;
      return nullptr;
    }else{
      return vec_pipeline[0];
    }
  }
  vk::structure::Pipeline* get_pipeline_byName(std::string name){
    for(int i=0; i<vec_pipeline.size(); i++){
      if(vec_pipeline[i]->definition.name == name){
        return vec_pipeline[i];
      }
    }
    std::cout<<"[error] Pipeline by name error -> "+ name +" not found"<<std::endl;
    return nullptr;
  }

  //Subpass info
  VkSubpassDescription description = {};
  VkSubpassDependency dependency = {};
  vk::structure::Command_buffer* command_buffer;
  vk::renderpass::Target target = vk::renderpass::SHADER;

  //Attachment
  vk::structure::Attachment depth;
  std::vector<vk::structure::Attachment> vec_color;
  std::vector<vk::structure::Attachment> vec_color_resolve;
  std::vector<vk::structure::Pipeline*> vec_pipeline;
  std::function<void(Subpass* subpass)> draw_task;

  //---------------------------
};

}
