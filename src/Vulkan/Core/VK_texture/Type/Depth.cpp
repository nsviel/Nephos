#include "Depth.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Depth::Depth(vk::Structure* vk_struct){
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
Depth::~Depth(){}

//Main function
void Depth::insert_depth(utl::base::Data& data, std::shared_ptr<utl::base::Depth> depth){
  if(!vk_ressource->check_texture(depth)) return;
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_retriever->retrieve_vk_object(data);
  if(!vk_object) return;

  //Check if image already inserted
  auto texture = vk_retriever->retrieve_vk_texture(*vk_object, depth->name);
  if(texture) return;

  //Create and insert texture
  auto new_texture = create_texture(depth);
  vk_object->map_texture[depth->name] = new_texture;

  //---------------------------
}
void Depth::update_depth(utl::base::Data& data, std::shared_ptr<utl::base::Depth> depth){
  if(!vk_ressource->check_texture(depth)) return;
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_retriever->retrieve_vk_object(data);
  if(!vk_object) return;

  //Retrieve data vk object
  auto texture = vk_retriever->retrieve_vk_texture(*vk_object, depth->name);
  if(!texture) return;

  //Check if size hasn't changed
  if(texture->stagger.size < texture->depth->size){
    vk_ressource->clean_texture(*texture);
    return;
  }

  //Copy and trasition
  vk_mem_transfer->copy_texture_to_gpu(*texture, texture->depth->data.data(), VK_IMAGE_LAYOUT_GENERAL);

  //---------------------------
}

//Subfunction
std::shared_ptr<vk::structure::Texture> Depth::create_texture(std::shared_ptr<utl::base::Depth> depth){
  //---------------------------

  //Texture definition
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->depth = depth;
  texture->UID = vk_uid->query_free_UID();
  texture->surface.format = vk_format->find_vk_format(depth->format);
  texture->surface.width = depth->width;
  texture->surface.height = depth->height;
  texture->surface.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  texture->surface.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

  //Create texture
  vk_image->create_image(texture->surface);
  vk_mem_allocator->allocate_empty_stagger_buffer(texture->stagger, depth->size * sizeof(uint16_t));
  vk_mem_transfer->copy_texture_to_gpu(*texture, depth->data.data(), VK_IMAGE_LAYOUT_GENERAL);

  //---------------------------
  return texture;
}

}
