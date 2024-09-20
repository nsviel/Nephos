#include "Data.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::texture{

//Constructor / Destructor
Data::Data(vk::Structure* vk_struct){
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
Data::~Data(){}

//Main function
void Data::insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> utl_image){
  //---------------------------
/*
  //Check image integrity
  if(!utl_image) return;
  if(utl_image->format == "") return;
  if(utl_image->size == 0) return;
  if(utl_image->width == 0) return;
  if(utl_image->height == 0) return;

  //Retrieve data vk object
  auto it_object = vk_struct->core.data.map_vk_object.find(data.UID);
  if(it_object == vk_struct->core.data.map_vk_object.end()) return;
  auto vk_object = it_object->second;

  //Check if image already inserted
  auto it_tex = vk_object->map_texture.find(utl_image->name);
  if(it_tex != vk_object->map_texture.end()) return;

  //Create texture from image
  auto texture = std::make_shared<vk::structure::Texture>();
  texture->image = utl_image;
  this->create_texture(texture);
*/
  //---------------------------
}

}
