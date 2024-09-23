#include "Image.h"

#include <Data/Image/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::img{

//Constructor / Destructor
Image::Image(dat::img::Node* node_image){
  //---------------------------

  vk::Node* node_vulkan = node_image->get_node_vulkan();
  dat::elm::Node* node_element = node_image->get_node_element();

  this->vk_data = node_vulkan->get_vk_data();
  this->dat_uid = node_element->get_dat_uid();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::add_image(dat::base::Entity& entity, std::shared_ptr<utl::media::Image> image){
  utl::base::Data& data = *entity.data;
  //----------------------------

  //Check if image already inseretd
  auto it = data.map_image.find(image->name);
  if(it != data.map_image.end()) return;

  //Else insert it
  image->UID = dat_uid->generate_UID();
  data.map_image[image->name] = image;
  vk_data->insert_image(data, image);

  //----------------------------
}

//Subfunction
std::shared_ptr<utl::media::Image> Image::get_image(dat::base::Entity& entity, std::string query){
  utl::base::Data& data = *entity.data;
  //----------------------------

  auto it = data.map_image.find(query);
  if(it != data.map_image.end()) return it->second;

  //----------------------------
  return nullptr;
}
std::shared_ptr<utl::media::Image> Image::get_or_create_image(dat::base::Entity& entity, std::string query){
  utl::base::Data& data = *entity.data;
  //----------------------------

  //Search for already existing image with same type
  auto it = data.map_image.find(query);
  if(it != data.map_image.end()) return it->second;

  //Else create it
  std::shared_ptr<utl::media::Image> image = std::make_shared<utl::media::Image>(query);
  this->add_image(entity, image);

  //----------------------------
  return image;
}

}
