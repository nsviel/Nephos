#include "Storage.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Storage::Storage(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_ressource = new vk::texture::Ressource(vk_struct);
  this->vk_retriever = new vk::data::Retriever(vk_struct);
  this->vk_format = new vk::image::Format(vk_struct);
  this->vk_image = new vk::image::Image(vk_struct);
  this->vk_uid = new vk::instance::UID(vk_struct);
  this->vk_mem_allocator = new vk::memory::Allocator(vk_struct);
  this->vk_mem_transfer = new vk::memory::Transfer(vk_struct);
  this->vk_transition = new vk::memory::Transition(vk_struct);

  //---------------------------
}
Storage::~Storage(){}

//Main function
void Storage::insert_storage(utl::base::Data& data, std::shared_ptr<utl::base::Storage> storage){
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_retriever->retrieve_vk_object(data);
  if(!vk_object) return;

  //Check if image already inserted
  auto vk_texture = vk_retriever->retrieve_vk_texture(*vk_object, storage->name);
  if(vk_texture) return;

  //Create and insert texture
  auto texture = create_texture(storage);
  vk_object->map_texture[storage->name] = texture;

  //---------------------------
}
void Storage::insert_empty_storage(utl::base::Data& data, std::shared_ptr<utl::base::Storage> storage){
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_retriever->retrieve_vk_object(data);
  if(!vk_object) return;

  //Check if image already inserted
  auto vk_texture = vk_retriever->retrieve_vk_texture(*vk_object, storage->name);
  if(vk_texture) return;

  //Create and insert texture



  auto texture = std::make_shared<vk::structure::Texture>();
  texture->storage = storage;
  texture->UID = vk_uid->query_free_UID();
  texture->surface.format = vk_format->find_vk_format(storage->format);
  texture->surface.width = storage->width;
  texture->surface.height = storage->height;
  texture->surface.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  texture->surface.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

  //Create texture
  vk_image->create_image(texture->surface);
  vk_transition->image_layout_transition(texture->surface, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_GENERAL);



  vk_object->map_texture[storage->name] = texture;

  //---------------------------
}
void Storage::update_storage(std::shared_ptr<utl::base::Storage> storage){
  if(!vk_ressource->check_texture(storage)) return;
  //---------------------------

  //Retrieve data vk object
  auto texture = vk_retriever->retrieve_vk_texture(*storage);
  if(!texture) return;

  //Check if size hasn't changed
  if(texture->stagger.size < texture->storage->size){
    vk_ressource->clean_texture(*texture);
    return;
  }

  //Copy and trasition
  vk_mem_transfer->copy_texture_to_gpu(*texture, texture->storage->data.data());
  vk_transition->image_layout_transition(texture->surface, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);

  //---------------------------
}

//Subfunction
std::shared_ptr<vk::structure::Texture> Storage::create_texture(std::shared_ptr<utl::base::Storage> storage){
  //---------------------------

  //Texture definition
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->storage = storage;
  texture->UID = vk_uid->query_free_UID();
  texture->surface.format = vk_format->find_vk_format(storage->format);
  texture->surface.width = storage->width;
  texture->surface.height = storage->height;
  texture->surface.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  texture->surface.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

  //Create texture
  vk_image->create_image(texture->surface);
  vk_mem_allocator->allocate_empty_stagger_buffer(texture->stagger, storage->size * sizeof(float));
  vk_mem_transfer->copy_texture_to_gpu(*texture, storage->data.data());
  vk_transition->image_layout_transition(texture->surface, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);

  //---------------------------
  return texture;
}

}
