#include "Ressource.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Ressource::Ressource(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_image = new vk::image::Ressource(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_buffer = new vk::data::Buffer(vk_struct);
  this->vk_screenshot = new vk::screenshot::Export(vk_struct);
  this->vk_format = new vk::image::Format(vk_struct);

  //---------------------------
}
Ressource::~Ressource(){}

//Main function
void Ressource::create_texture(vk::structure::Texture& texture){
  utl::base::Image& image = *texture.image;
  //---------------------------

  //Create associated vk_image
  texture.UID = vk_uid->query_free_UID();
  texture.surface.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  texture.surface.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  vk_image->create_image(texture.surface);

  //Make associated operation
  vk_mem_allocator->allocate_empty_stagger_buffer(texture.stagger, image.size);
  vk_mem_transfer->copy_texture_to_gpu(texture, image.data.data());

  //---------------------------
}
void Ressource::update_texture(vk::structure::Texture& texture){
  //---------------------------

  //Check if size hasn't changed
  if(texture.stagger.size < texture.image->size){
    this->clean_texture(texture);
    return;
  }

  vk_mem_transfer->copy_texture_to_gpu(texture,texture.image->data.data());

  //---------------------------
}
void Ressource::export_texture(vk::structure::Texture& texture){
  //---------------------------

  //vk_screenshot->export_image_to_jpeg(texture.surface);

  //---------------------------
}
void Ressource::clean_texture(vk::structure::Texture& texture){
  //---------------------------

  vk_image->clean_image(texture.surface);
  vk_buffer->clean_buffer(texture.stagger);

  //---------------------------
}
bool Ressource::check_texture(std::shared_ptr<utl::base::Texture> texture){
  //---------------------------

  if(!texture) return false;
  if(texture->format == "") return false;
  if(texture->width == 0) return false;
  if(texture->height == 0) return false;

  //---------------------------
  return true;
}

}
