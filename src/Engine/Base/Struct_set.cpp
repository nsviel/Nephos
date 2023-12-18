#include "Struct_set.h"


namespace eng::structure{

Set::Set(std::string name){
  //---------------------------

  this->name = name;

  //---------------------------
}

//Misc function
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_obj.size(); i++){
    eng::structure::Entity* entity = *next(list_obj.begin(), i);
    entity->is_visible = value;
  }

  //---------------------------
}

}
