#include "Struct_set.h"


namespace eng::structure{

Set::Set(std::string name){
  //---------------------------

  this->name = name;

  //---------------------------
}

//Misc function
void Set::add_new_set(std::string name){
  //---------------------------

  eng::structure::Set* set = new eng::structure::Set(name);
  list_set.push_back(set);
  this->nb_set++;

  //---------------------------
}
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    eng::structure::Entity* entity = *next(list_entity.begin(), i);
    entity->is_visible = value;
  }

  //---------------------------
}
void Set::select_next_object(){
  //----------------------------

  for(int i=0; i<list_entity.size(); i++){
    eng::structure::Entity* entity = *next(list_entity.begin(), i);

    if(selected_entity->ID == entity->ID){
      eng::structure::Entity* selection;

      if((i + 1) < list_entity.size()){
        selection = *next(list_entity.begin(), i + 1);
      }else{
        selection = *next(list_entity.begin(), 0);
      }

      this->selected_entity = selection;
    }
  }

  //----------------------------
}

}
