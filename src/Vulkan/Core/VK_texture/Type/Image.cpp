#include "Image.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Image::Image(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_ressource = new vk::texture::Ressource(vk_struct);
  this->vk_retriever = new vk::data::Retriever(vk_struct);
  this->vk_format = new vk::image::Format(vk_struct);
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::insert_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> image){
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_retriever->retrieve_vk_object(data);
  if(!vk_object) return;

  //Check if image already inserted
  auto vk_texture = vk_retriever->retrieve_vk_texture(*vk_object, image->name);
  if(vk_texture) return;

  //Create and insert texture
  auto texture = create_texture(image);
  vk_object->map_texture[image->name] = texture;

  //---------------------------
}
void Image::insert_image(std::shared_ptr<utl::base::Image> image){
  if(!vk_ressource->check_texture(image)) return;
  //---------------------------

  //Check if image already inserted
  auto vk_texture = vk_retriever->retrieve_vk_texture(*image);
  if(vk_texture) return;

  //Create and insert texture
  auto texture = create_texture(image);

  //---------------------------
}
void Image::update_image(std::shared_ptr<utl::base::Image> image){
  if(!vk_ressource->check_texture(image)) return;
  //---------------------------

  //Retrieve data vk object
  auto texture = vk_retriever->retrieve_vk_texture(*image);
  if(!texture) return;

  //Check if size hasn't changed
  if(texture->stagger.size < texture->image->size){
    vk_ressource->clean_texture(*texture);
    return;
  }

  vk_mem_transfer->copy_texture_to_gpu(*texture, texture->image->data.data());

  //---------------------------
}

//Subfunction
std::shared_ptr<vk::structure::Texture> Image::create_texture(std::shared_ptr<utl::base::Image> image){
  //---------------------------

  //Texture definition
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->image = image;
  texture->UID = vk_uid->query_free_UID();
  texture->surface.format = vk_format->find_vk_format(image->format);
  texture->surface.width = image->width;
  texture->surface.height = image->height;
  texture->surface.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  texture->surface.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

  //Create texture
  vk_image->create_image(texture->surface);
  vk_mem_allocator->allocate_empty_stagger_buffer(texture->stagger, image->size);
  vk_mem_transfer->copy_texture_to_gpu(*texture, image->data.data());

  //---------------------------
  return texture;
}
void Image::clean_texture(vk::structure::Object& vk_object){
  //---------------------------

  for(auto& [name, texture] : vk_object.map_texture){
    vk_ressource->clean_texture(*texture);
  }

  //---------------------------
}

}
