#include "Set.h"


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
    entity->update_pose();
  }

  // Recursively process nested sets
  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* nested_set = *next(list_subset.begin(), i);
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
  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* set = *next(list_subset.begin(), i);
    set->reset();
  }

  //---------------------------
}

//Set function
void Set::add_set(utl::type::Set* set){
  //---------------------------

  set->set_parent = this;
  list_subset.push_back(set);
  this->nb_set++;
  this->select_next_entity();
  if(set->nb_entity != 0){
    this->selected_set = set;
  }

  //---------------------------
}
void Set::add_new_set(std::string name){
  //---------------------------

  utl::type::Set* set = new utl::type::Set(name);
  set->set_parent = this;
  list_subset.push_back(set);
  this->nb_set++;
  this->selected_set = set;

  //---------------------------
}

//Entity function
void Set::insert_entity(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  entity->set_parent = this;
  this->list_entity.push_back(entity);
  this->nb_entity++;

  this->selected_entity = entity;
  set_parent->selected_entity = entity;

  //---------------------------
}
void Set::delete_entity(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  // Check if the current set has the query entity
  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);

    if(selected_entity->UID == entity->UID){
      this->list_entity.remove(entity);
      this->nb_entity--;
      entity->remove_entity();
      this->select_next_entity();
      delete entity;
      entity = nullptr;
      return;
    }
  }

  // Recursively call delete_entity for each nested set
  for(utl::type::Set* subset : list_subset){
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
  for(utl::type::Set* subset : list_subset){
    subset->delete_entity_all();
  }

  //---------------------------
}
void Set::delete_entity_selected(){
  //---------------------------

  this->list_entity.remove(selected_entity);
  this->nb_entity--;
  selected_entity->remove_entity();

  //---------------------------
}
void Set::select_next_entity(){
  //----------------------------

  if(list_entity.size() == 0){
    this->selected_entity = nullptr;
    set_parent->selected_entity = nullptr;
    return;
  }

  // Check if the current set has a selected entity
  if(selected_entity != nullptr){
    for(auto it = list_entity.begin(); it != list_entity.end(); ++it){
      utl::type::Entity* entity = *it;

      if(selected_entity->UID == entity->UID){
        auto next_it = std::next(it);

        if(next_it != list_entity.end()){
          this->selected_entity = *next_it;
        } else {
          // If at the end of the list, cycle back to the beginning
          selected_entity = *list_entity.begin();
        }

        set_parent->selected_entity = selected_entity;
        return;
      }
    }
  }

  // Recursively call select_next_entity for each nested subset
  for (Set* subset : list_subset) {
    subset->select_next_entity();

    // Check if the selected entity is in the current subset
    if (subset->selected_entity != nullptr) {
      selected_entity = subset->selected_entity;
      set_parent->selected_entity = selected_entity;
      return; // Stop searching if found in a subset
    }
  }

  //----------------------------
}
void Set::set_selected_entity(utl::type::Entity* entity_to_select){
  //---------------------------

  this->selected_entity = entity_to_select;
  set_parent->selected_entity = selected_entity;

  //---------------------------
}

//Subfunction
int Set::get_nb_entity(){
  int nb_entity = 0;
  //---------------------------

  nb_entity += list_entity.size();

  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* subset = *next(list_subset.begin(), i);
    nb_entity += subset->get_nb_entity();
  }

  //---------------------------
  return nb_entity;
}
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);
    entity->visibility_entity(value);
  }

  //---------------------------
}
int Set::compute_number_point(){
  int nb_point = 0;
  //---------------------------

  // Add the points in the current set
  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);
    utl::type::Data* data = entity->get_data();
    nb_point += data->nb_point;
  }

  // Recursively add points from nested subsets
  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* subset = *next(list_subset.begin(), i);
    nb_point += subset->compute_number_point();
  }

  //---------------------------
  return nb_point;
}
utl::type::Set* Set::get_set(std::string name){
  //---------------------------

  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* set = *next(list_subset.begin(),i);
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
