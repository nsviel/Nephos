#include "Set.h"

#include <Scene/Namespace.h>


namespace eng::scene{

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
  for (int i=0; i<set->list_entity.size(); i++){
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

//Entity function
void Set::delete_entity_all(utl::type::Set* set){
  //---------------------------

  // Check if the current set has the query entity
  for(int i=0; i<set->list_entity.size(); i++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), i);

    set->list_entity.remove(entity);
    set->nb_entity--;
    entity->remove_entity();
  }

  // Recursively call delete_entity_recursive for each nested set
  for(utl::type::Set* subset : set->list_subset){
    this->delete_entity_all(subset);
  }

  //---------------------------
}
void Set::delete_entity_selected(utl::type::Set* set){
  //---------------------------

  set->list_entity.remove(set->selected_entity);
  set->nb_entity--;
  set->selected_entity->remove_entity();

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
    nb_point += data->point.size;
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
