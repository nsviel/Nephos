#include "Set.h"

#include <Scene/Namespace.h>


namespace dat{

//Constructor / Destructor
Set::Set(){
  //---------------------------


  //---------------------------
}
Set::~Set(){}

//Set function
void Set::update_set(utl::type::Set* set){
  //---------------------------

  // Process entities within the current set
  for(int i=0; i<set->list_entity.size(); i++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), i);
    entity->update_pose();
  }

  // Recursively process nested sets
  for(int i=0; i<set->list_subset.size(); i++){
    utl::type::Set* subset = *next(set->list_subset.begin(), i);
    this->update_set(subset);
  }

  //---------------------------
}
void Set::reset_set(utl::type::Set* set){
  //---------------------------

  //Reset all associated entities
  for(int j=0; j<set->list_entity.size(); j++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), j);
    entity->reset_entity();
  }

  //Reset all associated sets
  for(int i=0; i<set->list_subset.size(); i++){
    utl::type::Set* subset = *next(set->list_subset.begin(), i);
    this->reset_set(subset);
  }

  //---------------------------
}
void Set::visibility_set(utl::type::Set* set, bool value){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), i);
    entity->set_visibility(value);
  }

  //---------------------------
}

//Subset function
void Set::add_subset(utl::type::Set* set, utl::type::Set* subset){
  //---------------------------

  subset->set_parent = set;
  set->list_subset.push_back(subset);
  set->nb_subset++;

  if(subset->nb_entity != 0){
    set->selected_subset = subset;
  }

  //---------------------------
}
utl::type::Set* Set::create_subset(utl::type::Set* set, std::string name){
  //---------------------------

  utl::type::Set* subset = new utl::type::Set();
  subset->name = name;
  subset->set_parent = set;
  subset->is_suppressible = true;

  set->nb_subset++;
  set->selected_subset = subset;
  set->list_subset.push_back(subset);

  //---------------------------
  return subset;
}
utl::type::Set* Set::get_subset(utl::type::Set* set, std::string name){
  //---------------------------

  for(int i=0; i<set->list_subset.size(); i++){
    utl::type::Set* subset = *next(set->list_subset.begin(),i);
    if(subset->name == name){
      return subset;
    }
  }

  std::cout<<"[error] Subset not found ["<<name<<"]"<<std::endl;

  //---------------------------
  return nullptr;
}
utl::type::Set* Set::get_or_create_subset(utl::type::Set* set, std::string name){
  //---------------------------

  for(int i=0; i<set->list_subset.size(); i++){
    utl::type::Set* subset_in_list = *next(set->list_subset.begin(),i);
    if(subset_in_list->name == name){
      return subset_in_list;
    }
  }

  utl::type::Set* subset = create_subset(set, name);

  //---------------------------
  return subset;
}

//Entity function
void Set::insert_entity(utl::type::Set* set, utl::type::Entity* entity){
  if(set == nullptr || entity == nullptr) return;
  //---------------------------

  entity->set_parent = set;
  set->list_entity.push_back(entity);
  set->nb_entity++;
  this->select_entity(set, entity);

  //---------------------------
}
void Set::remove_entity(utl::type::Set* set, utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //If set locked, remove all
  if(set->is_locked){
    this->remove_entity_all(set);
    return;
  }

  // Check if the current set has the query entity
  for(int i=0; i<set->list_entity.size(); i++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), i);

    if(set->selected_entity->UID == entity->UID){
      this->select_entity_next(set);

      set->list_entity.remove(entity);
      set->nb_entity--;

      entity->remove_entity();
      delete entity;

      return;
    }
  }

  // Recursively call remove_entity for each nested set
  for(utl::type::Set* subset : set->list_subset){
    this->remove_entity(subset, entity);
  }

  //---------------------------
}

void Set::remove_entity_all(utl::type::Set* set){
  if(set->list_entity.size() == 0) return;
  //---------------------------

  // Check if the current set has the query entity
  auto it = set->list_entity.begin();
  while(it != set->list_entity.end()){
    utl::type::Entity* entity = *it;

    it = set->list_entity.erase(it);
    set->nb_entity--;

    entity->remove_entity();
    delete entity;
  }

  // Recursively call remove_entity_recursive for each nested set
  for(utl::type::Set* subset : set->list_subset){
    this->remove_entity_all(subset);
  }

  //---------------------------
}
void Set::select_entity_next(utl::type::Set* set){
  //----------------------------

  if(set->list_entity.size() == 0){
    set->selected_entity = nullptr;
    set->set_parent->selected_entity = nullptr;
    return;
  }

  // Check if the current set has a selected entity
  if(set->selected_entity != nullptr){
    for(auto it = set->list_entity.begin(); it != set->list_entity.end(); ++it){
      utl::type::Entity* entity = *it;

      if(set->selected_entity->UID == entity->UID){
        auto next_it = std::next(it);

        if(next_it != set->list_entity.end()){
          set->selected_entity = *next_it;
        } else {
          // If at the end of the list, cycle back to the beginning
          set->selected_entity = *set->list_entity.begin();
        }

        set->set_parent->selected_entity = set->selected_entity;
        return;
      }
    }
  }

  // Recursively call select_entity_next for each nested subset
  for(utl::type::Set* subset : set->list_subset){
    this->select_entity_next(subset);

    // Check if the selected entity is in the current subset
    if(subset->selected_entity != nullptr){
      set->selected_entity = subset->selected_entity;
      set->set_parent->selected_entity = set->selected_entity;
      return; // Stop searching if found in a subset
    }
  }

  //----------------------------
}
void Set::select_entity(utl::type::Set* set, utl::type::Entity* entity){
  //---------------------------

  set->selected_entity = entity;

  // Propagate the selection to the parent sets
  utl::type::Set* current_parent = set->set_parent;
  while(current_parent != nullptr){
    current_parent->selected_entity = entity;
    current_parent = current_parent->set_parent; // Move to the next parent set
  }

  // Recursively select the entity for all subsets
  for (auto subset : set->list_subset) {
    this->select_entity(subset, entity);
  }

  //---------------------------
}
bool Set::is_selected_entity(utl::type::Set* set, utl::type::Entity* entity){
  return entity->UID == set->selected_entity->UID;
}

//Subfunction
int Set::compute_number_entity(utl::type::Set* set){
  int nb_entity = 0;
  //---------------------------

  nb_entity += set->list_entity.size();

  for(int i=0; i<set->list_subset.size(); i++){
    utl::type::Set* subset = *next(set->list_subset.begin(), i);
    nb_entity += compute_number_entity(subset);
  }

  //---------------------------
  return nb_entity;
}
int Set::compute_number_point(utl::type::Set* set){
  int nb_point = 0;
  //---------------------------

  // Add the points in the current set
  for(int i=0; i<set->list_entity.size(); i++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), i);
    utl::type::Data* data = entity->get_data();
    nb_point += data->size;
  }

  // Recursively add points from nested subsets
  for(int i=0; i<set->list_subset.size(); i++){
    utl::type::Set* subset = *next(set->list_subset.begin(), i);
    nb_point += compute_number_point(subset);
  }

  //---------------------------
  return nb_point;
}

}