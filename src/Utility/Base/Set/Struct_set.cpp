#include "Struct_set.h"


namespace utl::base{

Set::Set(std::string name){
  //---------------------------

  this->name = name;

  //---------------------------
}

//Misc function
void Set::add_new_set(std::string name){
  //---------------------------

  utl::base::Set* set = new utl::base::Set(name);
  list_set.push_back(set);
  this->nb_set++;

  //---------------------------
}
void Set::reset(){
  //---------------------------

  //Reset all associated entities
  for(int j=0; j<list_entity.size(); j++){
    entity::Entity* entity = *next(list_entity.begin(), j);
    entity->reset_entity();
  }

  //Reset all associated sets
  for(int i=0; i<list_set.size(); i++){
    utl::base::Set* set = *next(list_set.begin(), i);
    set->reset();
  }

  //---------------------------
}
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    entity::Entity* entity = *next(list_entity.begin(), i);
    entity->visibility_entity(value);
  }

  //---------------------------
}
void Set::select_next_entity(){
  //----------------------------

  for(int i=0; i<list_entity.size(); i++){
    entity::Entity* entity = *next(list_entity.begin(), i);

    if(this->selected_entity->UID == entity->UID){
      entity::Entity* next_entity;

      if((i + 1) < list_entity.size()){
        next_entity = *next(list_entity.begin(), i + 1);
      }else{
        next_entity = *next(list_entity.begin(), 0);
      }

      this->selected_entity = next_entity;
      return;
    }
  }

  //----------------------------
  this->selected_entity = nullptr;
}
void Set::insert_entity(entity::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  this->list_entity.push_back(entity);
  this->selected_entity = entity;
  this->nb_entity++;

  //---------------------------
}
void Set::remove_entity(entity::Entity* entity){
  //---------------------------

  this->list_entity.remove(entity);
  this->nb_entity--;
  if(list_entity.size() == 0){
    this->selected_entity = nullptr;
  }

  //---------------------------
}
utl::base::Set* Set::get_set(std::string name){
  //---------------------------

  for(int i=0; i<list_set.size(); i++){
    utl::base::Set* set = *next(list_set.begin(),i);
    if(set->name == name){
      return set;
    }
  }

  std::cout<<"[error] Set not found ["<<name<<"]"<<std::endl;

  //---------------------------
  return nullptr;
}
entity::Entity* Set::get_entity(std::string name){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    entity::Entity* entity = *next(list_entity.begin(),i);
    if(entity->name == name){
      return entity;
    }
  }

  std::cout<<"[error] Entity not found ["<<name<<"]"<<std::endl;

  //---------------------------
  return nullptr;
}

}
