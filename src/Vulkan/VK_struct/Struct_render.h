#ifndef STRUCT_RENDER_H
#define STRUCT_RENDER_H

#include <ELE_specific/common.h>


struct Struct_render{
  //---------------------------

  int nb_frame;
  VkFormat required_image_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_B8G8R8A8_SRGB
  std::vector<Struct_renderpass*> vec_renderpass;
  VkViewport viewport;
  VkRect2D scissor;
  
  Struct_renderpass* get_renderpass_byName(std::string name){
    for(int i=0; i<vec_renderpass.size(); i++){
      if(vec_renderpass[i]->name == name){
        return vec_renderpass[i];
      }
    }
    std::cout<<"[error] Renderpass by name error -> "+ name +" not found"<<std::endl;
    return nullptr;
  }

  //---------------------------
};


#endif
