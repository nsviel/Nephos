#include "Element.h"

#include <Data/Element/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::elm{

//Constructor / Destructor
Element::Element(){
  //---------------------------


  //---------------------------
}
Element::~Element(){}

//Main function
std::shared_ptr<dat::base::Entity> Element::get_active_entity(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  // Attempt to cast to dat::base::Set
  if(auto set = std::dynamic_pointer_cast<dat::base::Set>(element)){
    return set->active_entity.lock();
  }
  // Attempt to cast to dat::base::Entity
  else if(auto entity = std::dynamic_pointer_cast<dat::base::Entity>(element)){
    return entity;
  }

  //---------------------------
  return nullptr;
}

}
