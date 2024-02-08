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
  this->vk_buffer = new vk::data::Buffer(struct_vulkan);
  this->vk_transfert = new vk::command::Transfert(struct_vulkan);

  //---------------------------
}
Texture::~Texture(){}

//Main function
vk::structure::Texture* Texture::load_texture(utl::media::Image* utl_image){
  if(utl_image->format == "") return nullptr;
  //---------------------------

  //Create texture container
  vk::structure::Texture* texture = new vk::structure::Texture();
  texture->utl_image = utl_image;

  //Create associated vk_image
  vk::structure::Image* image = &texture->vk_image;
  image->width = utl_image->width;
  image->height = utl_image->height;
  image->format = find_texture_format(utl_image);
  image->aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  image->usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  vk_image->create_image(image);

  //Create associated buffer
  vk::structure::Buffer* buffer = &texture->stagger;
  vk_memory->create_empty_stagger_buffer(buffer, utl_image->size);

  //Fill and store
  vk_transfert->copy_texture_to_gpu(texture);
  struct_vulkan->data.vec_texture.push_back(texture);

  //---------------------------
  return texture;
}
void Texture::update_texture(vk::structure::Texture* texture){
  //---------------------------

  //Check if size hasn't changed
  if(texture->stagger.size != texture->utl_image->size){
    texture = nullptr;
    return;
  }

  vk_transfert->copy_texture_to_gpu(texture);

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
void Texture::clean_texture(vk::structure::Object* vk_object){
  //---------------------------

  for(auto it = vk_object->list_texture.begin(); it != vk_object->list_texture.end();){
    vk::structure::Texture* texture = *it;

    vk_image->clean_image(&texture->vk_image);
    vk_buffer->clean_buffer(&texture->stagger);

    //delete texture;
    //it = vk_object->list_texture.erase(it);
  }

  //---------------------------
}
void Texture::clean(){
  //---------------------------

  for(int i=0; i<struct_vulkan->data.vec_texture.size(); i++){
    vk::structure::Texture* texture = struct_vulkan->data.vec_texture[i];
    vk_image->clean_image(&texture->vk_image);
    vk_buffer->clean_buffer(&texture->stagger);
  }

  //---------------------------
}

}
