#include "Entity.h"


namespace dat::base{

//Constructor / Destructor
Entity::Entity(){
  //---------------------------


  //---------------------------
}
Entity::~Entity(){}

//Main function
void Entity::add_image(utl::media::Image* image){
  //----------------------------

  //Check for already present image
  for(int i=0; i<list_image.size(); i++){
    utl::media::Image* image_in = *next(list_image.begin(), i);
    if(image->UID == image_in->UID) return;
  }

  //Else bind it
  this->list_image.push_back(image);

  //----------------------------
}


}
