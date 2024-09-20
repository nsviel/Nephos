#include "Ressource.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Ressource::Ressource(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_screenshot = new vk::image::Screenshot(vk_struct);
  this->vk_format = new vk::texture::Format(vk_struct);

  //---------------------------
}
Ressource::~Ressource(){}

//Main function
void Ressource::clean(){
  //---------------------------

  auto it =  vk_struct->core.data.list_vk_texture.begin();
  while(it !=  vk_struct->core.data.list_vk_texture.end()){
    std::shared_ptr<vk::structure::Texture> texture = *it;

    //Remove texture elements
    vk_image->clean_image(texture->wrapper);
    vk_buffer->clean_buffer(&texture->stagger);

    //Remove texture from list
    vk_struct->core.data.list_vk_texture.remove(texture);
    it = vk_struct->core.data.list_vk_texture.begin();
  }

  //---------------------------
}

//Texture function
void Ressource::create_texture(std::shared_ptr<vk::structure::Texture> texture){
  utl::media::Image& image = *texture->image;
  //---------------------------

  //Create texture container
  VkFormat format = vk_format->find_texture_format(texture->image);
  if(format == VK_FORMAT_UNDEFINED) return;

  //Create associated vk_image
  texture->wrapper.width = image.width;
  texture->wrapper.height = image.height;
  texture->wrapper.format = format;
  texture->wrapper.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  texture->wrapper.usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
  vk_image->create_image(texture->wrapper);

  //Make associated operation
  vk_mem_allocator->allocate_empty_stagger_buffer(texture->stagger, image.size);
  vk_mem_transfer->copy_texture_to_gpu(*texture);
  vk_struct->core.data.list_vk_texture.push_back(texture);

  //---------------------------
}
void Ressource::update_texture(std::shared_ptr<vk::structure::Texture> texture){
  //---------------------------

  //Check if size hasn't changed
  if(texture->stagger.size < texture->image->size){
    this->clean_texture(texture);
    return;
  }

  vk_mem_transfer->copy_texture_to_gpu(*texture);

  //---------------------------
}
void Ressource::export_texture(std::shared_ptr<vk::structure::Texture> texture){
  if(!texture) return;
  //---------------------------

  vk_screenshot->export_image_to_jpeg(texture->wrapper);

  //---------------------------
}
void Ressource::clean_texture(std::shared_ptr<vk::structure::Texture> texture){
  //---------------------------

  vk_image->clean_image(texture->wrapper);
  vk_buffer->clean_buffer(&texture->stagger);
  texture->image->texture_ID = -1;

  //---------------------------
}

//Texture subfunction


//Subfunction
std::shared_ptr<vk::structure::Texture> Ressource::query_texture(int UID){
  //---------------------------
/*
  for(auto& texture : vk_struct->core.data.list_vk_texture){
    if(texture->image->UID == UID){
      return texture;
    }
  }*/

  //---------------------------
  return nullptr;
}

}
