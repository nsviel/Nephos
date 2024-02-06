#include "Texture.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::main{

//Constructor / Destructor
Texture::Texture(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_image = new vk::image::Image(struct_vulkan);
  this->vk_memory = new vk::command::Memory(struct_vulkan);

  //---------------------------
}
Texture::~Texture(){}

//Main function
vk::structure::Texture* Texture::load_texture(utl::media::Image* struct_image){
  //---------------------------

  vk::structure::Texture* texture = new vk::structure::Texture();

  texture->utl_image = struct_image;
  texture->vk_image.width = struct_image->width;
  texture->vk_image.height = struct_image->height;
  texture->vk_image.data = &struct_image->data;

  texture->vk_image.format = find_texture_format(struct_image);
  texture->vk_image.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  texture->vk_image.usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  vk_image->create_image(&texture->vk_image);
  vk_memory->transfert_image_to_gpu(&texture->vk_image);

  struct_vulkan->data.vec_texture.push_back(texture);

  //---------------------------
  return texture;
}
void Texture::update_texture(vk::structure::Texture* texture){
  //---------------------------

  vk_memory->transfert_image_to_gpu(&texture->vk_image);

  //---------------------------
}
VkFormat Texture::find_texture_format(utl::media::Image* image){
  VkFormat format;
  //---------------------------

  if(image->format == "R8G8B8A8_SRGB" || image->format == "MJPEG"){
    format = VK_FORMAT_R8G8B8A8_SRGB;
  }
  else if(image->format == "B8G8R8A8_SRGB"){
    format = VK_FORMAT_B8G8R8A8_SRGB;
  }
  else if(image->format == "R16_UNORM"){
    format = VK_FORMAT_R16_UNORM;
  }
  else if(image->format == "R16_UINT"){
    format = VK_FORMAT_R16_UINT;
  }
  else if(image->format == "R32_UINT"){
    format = VK_FORMAT_R32_UINT;
  }
  else if(image->format == "R16UI"){
    format = VK_FORMAT_R16_UINT;
  }
  else{
    cout<<"[error] texture format not recognized [-> "<<image->format<<"]"<<endl;
  }

  //---------------------------
  return format;
}

//Texture cleaning
void Texture::clean_texture(vk::structure::Object* data){
  //---------------------------

  for(int i=0; i<data->list_texture.size(); i++){
    vk::structure::Texture* texture = *next(data->list_texture.begin(), i);
    vk_image->clean_image(&texture->vk_image);
  }

  //---------------------------
}
void Texture::clean(){
  //---------------------------

  for(int i=0; i<struct_vulkan->data.vec_texture.size(); i++){
    vk::structure::Texture* texture = struct_vulkan->data.vec_texture[i];
    vk_image->clean_image(&texture->vk_image);
  }

  //---------------------------
}

}
