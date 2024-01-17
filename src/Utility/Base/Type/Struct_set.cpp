#include "Struct_set.h"


namespace utl::type{

Set::Set(){
  //---------------------------


  //---------------------------
}
Set::Set(std::string name){
  //---------------------------

  this->name = name;

  //---------------------------
}

//Main function
void Set::update(){
  //---------------------------

  // Process entities within the current set
  for (int i=0; i<list_entity.size(); i++){
    entity::Entity* entity = *next(list_entity.begin(), i);
    entity->update_entity();
  }

  // Recursively process nested sets
  for(int i=0; i<list_set.size(); i++){
    utl::type::Set* nested_set = *next(list_set.begin(), i);
    nested_set->update();
  }

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
    utl::type::Set* set = *next(list_set.begin(), i);
    set->reset();
  }

  //---------------------------
}

//Add element
void Set::add_set(utl::type::Set* set){
  //---------------------------

  list_set.push_back(set);
  this->nb_set++;

  //---------------------------
}
void Set::add_new_set(std::string name){
  //---------------------------

  utl::type::Set* set = new utl::type::Set(name);
  list_set.push_back(set);
  this->nb_set++;

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

//Parameter
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    entity::Entity* entity = *next(list_entity.begin(), i);
    entity->visibility_entity(value);
  }

  //---------------------------
}
utl::type::Set* Set::get_set(std::string name){
  //---------------------------

  for(int i=0; i<list_set.size(); i++){
    utl::type::Set* set = *next(list_set.begin(),i);
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
