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
    eng::structure::Object* object = *next(list_obj.begin(), i);
    object->is_visible = value;
  }

  //---------------------------
}

}
