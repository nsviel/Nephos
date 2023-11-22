#include "VK_texture.h"

#include <VK_image/VK_image.h>
#include <VK_command/VK_memory.h>
#include <VK_main/Struct_vulkan.h>
#include <UTL_file/File.h>
#include <UTL_file/Image.h>


//Constructor / Destructor
VK_texture::VK_texture(Struct_vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_image = new VK_image(struct_vulkan);
  this->vk_memory = new VK_memory(struct_vulkan);

  //---------------------------
}
VK_texture::~VK_texture(){}

//Main function
Struct_vk_image* VK_texture::load_texture(Struct_image* struct_image){
  //---------------------------

  Struct_vk_image* image = new Struct_vk_image();
  image->data = struct_image->buffer;
  image->width = struct_image->width;
  image->height = struct_image->height;
  image->format = find_texture_format(struct_image);
  image->aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  image->usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  vk_image->create_image(image);
  vk_memory->transfert_image_to_gpu(image);

  struct_vulkan->data.vec_texture.push_back(image);

  //---------------------------
  return image;
}
void VK_texture::update_texture(Struct_vk_image* image){
  //---------------------------

  vk_memory->transfert_image_to_gpu(image);

  //---------------------------
}
VkFormat VK_texture::find_texture_format(Struct_image* image){
  VkFormat format;
  //---------------------------

  if(image->format == "R8G8B8A8_SRGB"){
    format = VK_FORMAT_R8G8B8A8_SRGB;
  }
  else if(image->format == "B8G8R8A8_SRGB"){
    format = VK_FORMAT_B8G8R8A8_SRGB;
  }
  else if(image->format == "R16_UNORM"){
    format = VK_FORMAT_R16_UNORM;
  }
  else if(image->format == "R32_UINT"){
    format = VK_FORMAT_R32_UINT;
  }
  else if(image->format == "R16UI"){
    format = VK_FORMAT_R16_UINT;
  }
  else{
    cout<<"[error] texture format not recognized ["<<image->format<<"]"<<endl;
  }

  //---------------------------
  return format;
}

//Texture cleaning
void VK_texture::clean_texture(Struct_vk_entity* data){
  //---------------------------

  for(int i=0; i<data->list_texture.size(); i++){
    Struct_vk_image* image = *next(data->list_texture.begin(), i);
    vk_image->clean_image(image);
  }

  //---------------------------
}
void VK_texture::clean_textures(){
  //---------------------------

  for(int i=0; i<struct_vulkan->data.vec_texture.size(); i++){
    vk_image->clean_image(struct_vulkan->data.vec_texture[i]);
  }

  //---------------------------
}
