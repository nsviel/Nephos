#include "Image.h"

#include <Data/Image/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::img{

//Constructor / Destructor
Image::Image(dat::img::Node* node_image){
  //---------------------------

  dat::elm::Node* node_element = node_image->get_node_element();

  this->dat_uid = node_element->get_dat_uid();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::add_image(dat::base::Entity& entity, std::shared_ptr<utl::media::Image> image){
  //----------------------------

  //Check if image already inseretd
  auto& is_image = entity.data->map_image[image->name];
  if(is_image) return;

  //Else insert it
  this->manage_UID(image);
  entity.data->map_image[image->name] = image;

  //----------------------------
}
void Image::manage_UID(std::shared_ptr<utl::media::Image> image){
  //----------------------------

  if(image->UID == -1){
    image->UID = dat_uid->generate_UID();
  }

  //----------------------------
}

//Subfunction
bool Image::is_image_inserted(dat::base::Entity& entity, int UID){
  //----------------------------

  //Search for already existing image with same type
  for(auto& [name, texture] : entity.data->map_image){
    if(texture->UID == UID) return true;
  }

  //----------------------------
  return false;
}
std::shared_ptr<utl::media::Image> Image::get_image(dat::base::Entity& entity, std::string query){
  if(query == "") return nullptr;
  //----------------------------

  auto& image = entity.data->map_image[query];
  if(image) return image;

  //----------------------------
  return nullptr;
}
std::shared_ptr<utl::media::Image> Image::get_or_create_image(dat::base::Entity& entity, std::string query){
  if(query == "") return nullptr;
  //----------------------------

  //Search for already existing image with same type
  auto& image = entity.data->map_image[query];
  if(image) return image;

  //Else create it
  std::shared_ptr<utl::media::Image> new_image = std::make_shared<utl::media::Image>();
  new_image->name = query;
  this->add_image(entity, new_image);

  //----------------------------
  return new_image;
}

}
