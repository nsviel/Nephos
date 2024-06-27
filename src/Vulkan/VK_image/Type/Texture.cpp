#include "Texture.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::image{

//Constructor / Destructor
Texture::Texture(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_screenshot = new vk::image::Screenshot(vk_struct);

  //---------------------------
}
Texture::~Texture(){}

//Main function
void Texture::clean(){
  list<vk::structure::Texture*>& list_vk_texture = vk_struct->data.list_vk_texture;
  //---------------------------

  for(int i=0; i<list_vk_texture.size(); i++){
    vk::structure::Texture* texture = *next(list_vk_texture.begin(),i);

    vk_image->clean_image(&texture->vk_image);
    vk_buffer->clean_buffer(&texture->stagger);
  }

  //---------------------------
}

//Texture function
void Texture::import_texture(utl::media::Image* utl_image){
  //---------------------------

  //Input image checks
  if(utl_image->format == "") return;
  if(utl_image->width == 0 || utl_image->height == 0) return;

  //If the texture exists, update it
  vk::structure::Texture* texture = query_texture(utl_image->texture_ID);
  if(texture != nullptr){
    texture->utl_image = utl_image;
    this->update_texture(texture);
  }
  //Else create it
  else{
    texture = new vk::structure::Texture();
    texture->utl_image = utl_image;
    this->create_texture(texture);
  }

  //---------------------------
}
void Texture::export_texture(utl::media::Image* utl_image){
  //---------------------------

  vk::structure::Texture* texture = query_texture(utl_image->texture_ID);
  if(texture == nullptr) return;

  vk_screenshot->export_image_to_jpeg(&texture->vk_image);

  //---------------------------
}
void Texture::clean_texture(vk::structure::Texture* texture){
  //---------------------------

  vk_image->clean_image(&texture->vk_image);
  vk_buffer->clean_buffer(&texture->stagger);
  texture->utl_image->texture_ID = -1;
  texture = {};
  delete texture;

  //---------------------------
}

//Texture subfunction
void Texture::update_texture(vk::structure::Texture* texture){
  //---------------------------

  //Check if size hasn't changed
  if(texture->stagger.size < texture->utl_image->size){
    this->clean_texture(texture);
    return;
  }

  vk_mem_transfer->copy_texture_to_gpu(texture);

  //---------------------------
}
void Texture::create_texture(vk::structure::Texture* texture){
  //---------------------------

  //Create texture container
  texture->UID = vk_uid->query_free_UID();
  texture->utl_image->texture_ID = texture->UID;

  //Create associated vk_image
  vk::structure::Image* image = &texture->vk_image;
  image->width = texture->utl_image->width;
  image->height = texture->utl_image->height;
  image->format = find_texture_format(texture->utl_image);
  image->aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  image->usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  vk_image->create_image(image);

  //Make associated operation
  vk_mem_allocator->allocate_empty_stagger_buffer(&texture->stagger, texture->utl_image->size);
  vk_mem_transfer->copy_texture_to_gpu(texture);
  vk_struct->data.list_vk_texture.push_back(texture);

  //---------------------------
}

//Subfunction
void Texture::clean_texture(vk::structure::Object* vk_object){
  //---------------------------

  for(auto it = vk_object->list_vk_texture.begin(); it != vk_object->list_vk_texture.end();){
    vk::structure::Texture* texture = *it;
    this->clean_texture(texture);
  }

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
vk::structure::Texture* Texture::query_texture(int UID){
  list<vk::structure::Texture*>& list_vk_texture = vk_struct->data.list_vk_texture;
  //---------------------------

  for(int i=0; i<list_vk_texture.size(); i++){
    vk::structure::Texture* texture = *next(list_vk_texture.begin(),i);

    if(texture->UID == UID){
      return texture;
    }
  }

  //---------------------------
  return nullptr;
}

}