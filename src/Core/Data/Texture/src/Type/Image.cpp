#include "Image.h"

#include <Data/Texture/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::img{

//Constructor / Destructor
Image::Image(dat::img::Node* node_image){
  //---------------------------

  vk::Node* node_vulkan = node_image->get_node_vulkan();
  dat::elm::Node* node_element = node_image->get_node_element();

  this->vk_texture = node_vulkan->get_vk_texture();
  this->dat_uid = node_element->get_dat_uid();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::add_image(dat::base::Entity& entity, std::shared_ptr<utl::base::Image> image){
  utl::base::Data& data = *entity.data;
  //----------------------------

  if(image->size == 0) return;
  if(image->width == 0) return;
  if(image->height == 0) return;

  //Check if image already inseretd
  auto it = data.map_image.find(image->name);
  if(it == data.map_image.end()){
    this->insert_image(entity, image);
  }

  //----------------------------
}

//Subfunction
void Image::insert_image(dat::base::Entity& entity, std::shared_ptr<utl::base::Image> image){
  utl::base::Data& data = *entity.data;
  //----------------------------

  image->UID = dat_uid->generate_UID();
  data.map_image[image->name] = image;
  vk_texture->insert_image(data, image);

  //----------------------------
}
std::shared_ptr<utl::base::Image> Image::get_image(dat::base::Entity& entity, std::string query){
  utl::base::Data& data = *entity.data;
  //----------------------------

  auto it = data.map_image.find(query);
  if(it != data.map_image.end()) return it->second;

  //----------------------------
  return nullptr;
}
std::shared_ptr<utl::base::Image> Image::get_or_create_image(dat::base::Entity& entity, std::string query){
  utl::base::Data& data = *entity.data;
  //----------------------------

  //Search for already existing image with same type
  auto it = data.map_image.find(query);
  if(it != data.map_image.end()) return it->second;

  //Else create it
  std::shared_ptr<utl::base::Image> image = std::make_shared<utl::base::Image>(query);
  this->add_image(entity, image);

  //----------------------------
  return image;
}

}
