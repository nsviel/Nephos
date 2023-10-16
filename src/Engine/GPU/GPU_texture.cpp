#include "GPU_texture.h"

#include <Vulkan/Window/VK_surface.h>
#include <Vulkan/VK_engine.h>
#include <Vulkan/VK_struct.h>
#include <image/IconsFontAwesome5.h>
#include <Window/Window.h>


//Constructor / Destructor
GPU_texture::GPU_texture(VK_engine* vk_engine){
  //---------------------------

  this->vk_struct = vk_engine->get_vk_struct();
  this->vk_texture = vk_engine->get_vk_texture();

  //---------------------------
}
GPU_texture::~GPU_texture(){}

//Main function
Struct_image* GPU_texture::load_texture(string path){
  //---------------------------

  Struct_image* texture = vk_texture->load_texture(path);

  //---------------------------
  return texture;
}
void GPU_texture::clean_texture(Struct_image* texture){
  //---------------------------


  //---------------------------
}
