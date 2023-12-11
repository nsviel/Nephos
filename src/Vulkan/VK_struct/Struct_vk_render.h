#pragma once

#include <VK_struct/Struct_vk_renderpass.h>
#include <UTL_specific/common.h>


namespace vk::structure{

struct Struct_vk_render{
  //---------------------------

  int nb_frame;
  VkFormat required_image_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_B8G8R8A8_SRGB
  std::vector<vk::structure::Struct_vk_renderpass*> vec_renderpass;
  VkViewport viewport;
  VkRect2D scissor;

  vk::structure::Struct_vk_renderpass* get_renderpass_byName(std::string name){
    if(vec_renderpass.size() == 0){
      std::cout<<"[error] Renderpass vector empty"<<std::endl;
      exit(0);
    }
    for(int i=0; i<vec_renderpass.size(); i++){
      if(vec_renderpass[i]->name == name){
        return vec_renderpass[i];
      }
    }
    std::cout<<"[error] Renderpass by name error -> "+ name +" not found"<<std::endl;
    for(int i=0; i<vec_renderpass.size(); i++){
      std::cout<<vec_renderpass[i]->name<<std::endl;
    }
    return nullptr;
  }

  //---------------------------
};

}
