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

  this->manage_UID(image);
  if(has_image_UID(entity, image->UID)) return;
  if(image->format == "") image->format = "R8G8B8A8_SRGB";
  entity.list_image.push_back(image);

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
bool Image::has_image_UID(dat::base::Entity& entity, int UID){
  //----------------------------

  //Search for already existing image with same type
  for(auto& image : entity.list_image){
    if(image->UID == UID) return true;
  }

  //----------------------------
  return false;
}
std::shared_ptr<utl::media::Image> Image::get_image(dat::base::Entity& entity, std::string name){
  if(name == "") return nullptr;
  //----------------------------

  //Search for already existing image with same type
  for(auto& image : entity.list_image){
    if(image->name == name) return image;
  }

  //----------------------------
  return nullptr;
}
std::shared_ptr<utl::media::Image> Image::get_or_create_image(dat::base::Entity& entity, std::string name){
  if(name == "") return nullptr;
  //----------------------------

  //Search for already existing image with same type
  for(auto& image : entity.list_image){
    if(image->name == name) return image;
  }

  //Else create it
  std::shared_ptr<utl::media::Image> image = std::make_shared<utl::media::Image>();
  image->name = name;
  this->add_image(entity, image);

  //----------------------------
  return image;
}

}
