#ifndef VK_PARAM_H
#define VK_PARAM_H

#include <VK_struct/Struct_window.h>
#include <VK_struct/Struct_instance.h>
#include <VK_struct/Struct_device.h>
#include <VK_struct/Struct_swapchain.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_info.h>
#include <VK_struct/Struct_data.h>
#include <VK_struct/Struct_param.h>
#include <VK_struct/Struct_pool.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Struct_vulkan{
  //---------------------------

  //Element
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

  //Structure
  Struct_window window;
  Struct_instance instance;
  Struct_device device;
  Struct_swapchain swapchain;
  Struct_info info;
  Struct_data canvas;
  Struct_param param;
  Struct_pool pool;

  //Data
  std::vector<Struct_image*> vec_texture;
  std::list<Struct_data*> list_object;



  //---------------------------
};

#endif
