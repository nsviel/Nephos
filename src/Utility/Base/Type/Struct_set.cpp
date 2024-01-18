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
    utl::type::Entity* entity = *next(list_entity.begin(), i);
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
    utl::type::Entity* entity = *next(list_entity.begin(), j);
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

  set->set_parent = this;
  list_set.push_back(set);
  this->nb_set++;

  //---------------------------
}
void Set::add_new_set(std::string name){
  //---------------------------

  utl::type::Set* set = new utl::type::Set(name);
  set->set_parent = this;
  list_set.push_back(set);
  this->nb_set++;

  //---------------------------
}
void Set::select_next_entity(){
  //----------------------------

  // Check if the current set has a selected entity
  if(selected_entity != nullptr){
    for(int i=0; i<list_entity.size(); i++){
      utl::type::Entity* entity = *next(list_entity.begin(), i);

      if(selected_entity->UID == entity->UID){
        utl::type::Entity* next_entity;

        if ((i + 1) < list_entity.size()) {
          next_entity = *next(list_entity.begin(), i + 1);
        } else {
          next_entity = *next(list_entity.begin(), 0);
        }

        selected_entity = next_entity;
        return;
      }
    }
  }

  // Recursively call select_next_entity_recursive for each nested set
  for (Set* subset : list_set) {
    subset->select_next_entity();
  }

  //----------------------------
}
void Set::insert_entity(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  entity->set_parent = this;
  this->list_entity.push_back(entity);
  this->selected_entity = entity;
  this->nb_entity++;

  //---------------------------
}
void Set::delete_entity(utl::type::Entity* entity){
  //---------------------------

  // Check if the current set has the query entity
  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(selected_entity->UID == entity->UID){
      this->list_entity.remove(entity);
      this->nb_entity--;
      entity->remove_entity();
    }
  }

  // Recursively call delete_entity_recursive for each nested set
  for(utl::type::Set* subset : list_set){
    subset->delete_entity(entity);
  }

  //---------------------------
}
void Set::delete_entity_all(){
  //---------------------------

  // Check if the current set has the query entity
  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    this->list_entity.remove(entity);
    this->nb_entity--;
    entity->remove_entity();
  }

  // Recursively call delete_entity_recursive for each nested set
  for(utl::type::Set* subset : list_set){
    subset->delete_entity_all();
  }

  //---------------------------
}

//Parameter
void Set::set_selected_entity(utl::type::Entity* entity){
  //---------------------------

  //Check if we have the query entity in the current set list
  for(int i=0; i<list_entity.size(); i++) {
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(selected_entity->UID == entity->UID){
      this->selected_entity = entity;
    }
  }

  //---------------------------
}
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);
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
utl::type::Entity* Set::get_entity(std::string name){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(),i);
    if(entity->name == name){
      return entity;
    }
  }

  std::cout<<"[error] Entity not found ["<<name<<"]"<<std::endl;

  //---------------------------
  return nullptr;
}

}
