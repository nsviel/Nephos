#include "GPU_texture.h"

#include <Vulkan/VK_window/VK_surface.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <image/IconsFontAwesome5.h>
#include <ELE_window/Window.h>


//Constructor / Destructor
GPU_texture::GPU_texture(VK_engine* vk_engine){
  //---------------------------

  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_texture = vk_engine->get_vk_texture();

  //---------------------------
}
GPU_texture::~GPU_texture(){}

//Main function
Struct_image* GPU_texture::load_texture_from_file(string path){
  //---------------------------

  Struct_image* texture = vk_texture->load_texture_from_file(path);

  //---------------------------
  return texture;
}
Struct_image* GPU_texture::load_texture_from_frame(AVFrame* frame){
  //---------------------------

  Struct_image* texture = vk_texture->load_texture_from_frame(frame);

  //---------------------------
  return texture;
}
