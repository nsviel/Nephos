#include "Manager.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace ope::image{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------


  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::add_image(dat::base::Entity* entity, utl::media::Image* image){
  //----------------------------

  if(has_image(entity, image->type)) return;
  entity->list_image.push_back(image);

  //----------------------------
}
bool Manager::has_image(dat::base::Entity* entity, int type){
  //----------------------------

  //Search for already existing image with same type
  for(int i=0; i<entity->list_image.size(); i++){
    utl::media::Image* image = *next(entity->list_image.begin(), i);
    if(image->type == type) return true;
  }

  //----------------------------
  return false;
}
utl::media::Image* Manager::get_image(dat::base::Entity* entity, int type){
  //----------------------------

  //Search for already existing image with same type
  for(int i=0; i<entity->list_image.size(); i++){
    utl::media::Image* image = *next(entity->list_image.begin(), i);
    if(image->type == type) return image;
  }

  //----------------------------
  return nullptr;
}
utl::media::Image* Manager::get_or_create_image(dat::base::Entity* entity, int type){
  //----------------------------

  //Search for already existing image with same type
  for(int i=0; i<entity->list_image.size(); i++){
    utl::media::Image* image = *next(entity->list_image.begin(), i);
    if(image->type == type) return image;
  }

  utl::media::Image* image = new utl::media::Image();
  this->add_image(entity, image);

  //----------------------------
  return image;
}

}
