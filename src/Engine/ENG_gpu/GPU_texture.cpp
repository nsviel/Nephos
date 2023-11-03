#include "GPU_texture.h"

#include <VK_presentation/VK_surface.h>
#include <VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <image/IconsFontAwesome5.h>
#include <ELE_window/Window.h>


//Constructor / Destructor
GPU_texture::GPU_texture(VK_engine* vk_engine){
  //---------------------------

  this->struct_vulkan = vk_engine->get_struct_vulkan();
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
