#include "Image.h"

#include <Operation/Namespace.h>
#include <Element/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::element{

//Constructor / Destructor
Image::Image(dat::elm::Node* node_element){
  //---------------------------

  this->dat_uid = node_element->get_dat_uid();

  //---------------------------
}
Image::~Image(){}

//Main function
void Image::add_image(dat::base::Entity* entity, utl::media::Image* image){
  //----------------------------

  this->manage_UID(image);
  if(has_image_UID(entity, image->UID)) return;
  if(image->format == "") image->format = "R8G8B8A8_SRGB";
  entity->list_image.push_back(image);

  //----------------------------
}
void Image::manage_UID(utl::media::Image* image){
  //----------------------------

  if(image->UID == -1){
    image->UID = dat_uid->generate_UID();
  }

  //----------------------------
}

//Subfunction
bool Image::has_image_UID(dat::base::Entity* entity, int UID){
  //----------------------------

  //Search for already existing image with same type
  for(int i=0; i<entity->list_image.size(); i++){
    utl::media::Image* image = *next(entity->list_image.begin(), i);
    if(image->UID == UID) return true;
  }

  //----------------------------
  return false;
}
utl::media::Image* Image::get_image(dat::base::Entity* entity, std::string name){
  if(name == "") return nullptr;
  //----------------------------

  //Search for already existing image with same type
  for(int i=0; i<entity->list_image.size(); i++){
    utl::media::Image* image = *next(entity->list_image.begin(), i);
    if(image->name == name) return image;
  }

  //----------------------------
  return nullptr;
}
utl::media::Image* Image::get_or_create_image(dat::base::Entity* entity, std::string name){
  if(name == "") return nullptr;
  //----------------------------

  //Search for already existing image with same type
  for(int i=0; i<entity->list_image.size(); i++){
    utl::media::Image* image = *next(entity->list_image.begin(), i);
    if(image->name == name) return image;
  }

  //Else create it
  utl::media::Image* image = new utl::media::Image();
  image->name = name;
  this->add_image(entity, image);

  //----------------------------
  return image;
}

}
