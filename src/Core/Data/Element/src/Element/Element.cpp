#include "Element.h"

#include <Utility/Namespace.h>
#include <Element/Namespace.h>


namespace dat{

//Constructor / Destructor
Element::Element(){
  //---------------------------


  //---------------------------
}
Element::~Element(){}

//Main function
dat::base::Entity* Element::get_active_entity(utl::base::Element* element){
  //---------------------------

  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    return entity;
  }
  else if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    return set->active_entity;
  }

  //---------------------------
  return nullptr;
}

}
