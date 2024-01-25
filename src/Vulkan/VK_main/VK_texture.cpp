#include "VK_texture.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


//Constructor / Destructor
VK_texture::VK_texture(vk::structure::Vulkan* struct_vulkan){
  //---------------------------

  this->struct_vulkan = struct_vulkan;
  this->vk_image = new VK_image(struct_vulkan);
  this->vk_memory = new vk::command::VK_memory(struct_vulkan);

  //---------------------------
}
VK_texture::~VK_texture(){}

//Main function
vk::structure::Image* VK_texture::load_texture(utl::media::Image* struct_image){
  //---------------------------

  vk::structure::Image* image = new vk::structure::Image();
  image->data = struct_image->data;
  image->width = struct_image->width;
  image->height = struct_image->height;
  image->size = struct_image->size;
  image->format = find_texture_format(struct_image);
  image->aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  image->usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  vk_image->create_image(image);
  vk_memory->transfert_image_to_gpu(image);

  struct_vulkan->data.vec_texture.push_back(image);

  //---------------------------
  return image;
}
void VK_texture::update_texture(vk::structure::Image* image){
  //---------------------------

  vk_memory->transfert_image_to_gpu(image);

  //---------------------------
}
VkFormat VK_texture::find_texture_format(utl::media::Image* image){
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
void VK_texture::clean_texture(vk::structure::Object* data){
  //---------------------------

  for(int i=0; i<data->list_texture.size(); i++){
    vk::structure::Image* image = *next(data->list_texture.begin(), i);
    vk_image->clean_image(image);
  }

  //---------------------------
}
void VK_texture::clean(){
  //---------------------------

  for(int i=0; i<struct_vulkan->data.vec_texture.size(); i++){
    vk_image->clean_image(struct_vulkan->data.vec_texture[i]);
  }

  //---------------------------
}
