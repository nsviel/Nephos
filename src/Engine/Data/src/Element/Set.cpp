#include "Set.h"

#include <Data/Namespace.h>


namespace dat{

//Constructor / Destructor
Set::Set(dat::Node* node_data){
  //---------------------------

  this->dat_struct = node_data->get_data_struct();

  //---------------------------
}
Set::~Set(){}

//Set function
void Set::update_set(dat::base::Set* set){
  //---------------------------

  // Process entities within the current set
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    entity->update_pose();
  }

  // Recursively process nested sets
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->update_set(subset);
  }

  //---------------------------
}
void Set::reset_set(dat::base::Set* set){
  //---------------------------

  //Reset all associated entities
  for(int j=0; j<set->list_entity.size(); j++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), j);
    entity->reset_entity();
  }

  //Reset all associated sets
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->reset_set(subset);
  }

  //---------------------------
}
void Set::visibility_set(dat::base::Set* set, bool value){
  //---------------------------

  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    entity->set_visibility(value);
  }

  //---------------------------
}

//Subset function
void Set::add_subset(dat::base::Set* set, dat::base::Set* subset){
  //---------------------------

  subset->set_parent = set;
  set->list_subset.push_back(subset);
  set->nb_subset++;

  if(subset->nb_entity != 0){
    set->active_subset = subset;
  }

  //---------------------------
}
dat::base::Set* Set::create_subset(dat::base::Set* set, std::string name){
  //---------------------------

  dat::base::Set* subset = new dat::base::Set();
  subset->UID = dat_struct->UID++;
  subset->name = name;
  subset->set_parent = set;
  subset->is_suppressible = true;

  set->nb_subset++;
  set->active_subset = subset;
  set->list_subset.push_back(subset);

  //---------------------------
  return subset;
}
dat::base::Set* Set::get_subset(dat::base::Set* set, std::string name){
  //---------------------------

  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(),i);
    if(subset->name == name){
      return subset;
    }
  }

  std::cout<<"[error] Subset not found ["<<name<<"]"<<std::endl;

  //---------------------------
  return nullptr;
}
dat::base::Set* Set::get_or_create_subset(dat::base::Set* set, std::string name){
  //---------------------------

  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset_in_list = *next(set->list_subset.begin(),i);
    if(subset_in_list->name == name){
      return subset_in_list;
    }
  }

  dat::base::Set* subset = create_subset(set, name);

  //---------------------------
  return subset;
}

//Entity function
void Set::insert_entity(dat::base::Set* set, dat::base::Entity* entity){
  if(set == nullptr || entity == nullptr) return;
  //---------------------------

  entity->set_parent = set;
  set->list_entity.push_back(entity);
  set->nb_entity++;
  this->active_entity(set, entity);

  //---------------------------
}
void Set::remove_entity(dat::base::Set* set, dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //If set locked, remove all
  if(set->is_locked){
    this->remove_all_entity(set);
    return;
  }

  // Check if the current set has the query entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);

    if(set->active_entity->UID == entity->UID){
      this->active_next_entity(set);

      set->list_entity.remove(entity);
      set->nb_entity--;

      entity->remove_entity();
      delete entity;

      return;
    }
  }

  // Recursively call remove_entity for each nested set
  for(dat::base::Set* subset : set->list_subset){
    this->remove_entity(subset, entity);
  }

  //---------------------------
}
void Set::remove_all_entity(dat::base::Set* set){
  if(set->list_entity.size() == 0) return;
  //---------------------------

  // Check if the current set has the query entity
  auto it = set->list_entity.begin();
  while(it != set->list_entity.end()){
    dat::base::Entity* entity = *it;

    it = set->list_entity.erase(it);
    set->nb_entity--;

    entity->remove_entity();
    delete entity;
  }

  // Recursively call remove_entity_recursive for each nested set
  for(dat::base::Set* subset : set->list_subset){
    this->remove_all_entity(subset);
  }

  //---------------------------
}
void Set::active_next_entity(dat::base::Set* set){
  //----------------------------

  if(set->list_entity.size() == 0){
    set->active_entity = nullptr;
    set->set_parent->active_entity = nullptr;
    return;
  }

  // Check if the current set has a selected entity
  if(set->active_entity != nullptr){
    for(auto it = set->list_entity.begin(); it != set->list_entity.end(); ++it){
      dat::base::Entity* entity = *it;

      if(set->active_entity->UID == entity->UID){
        auto next_it = std::next(it);

        if(next_it != set->list_entity.end()){
          set->active_entity = *next_it;
        } else {
          // If at the end of the list, cycle back to the beginning
          set->active_entity = *set->list_entity.begin();
        }

        set->set_parent->active_entity = set->active_entity;
        return;
      }
    }
  }

  //----------------------------
}
void Set::active_entity(dat::base::Set* set, dat::base::Entity* entity){
  //---------------------------

  set->active_entity = entity;

  // Propagate the selection to the parent sets
  dat::base::Set* current_parent = set->set_parent;
  while(current_parent != nullptr){
    current_parent->active_entity = entity;
    current_parent = current_parent->set_parent; // Move to the next parent set
  }

  //---------------------------
}
bool Set::is_entity_active(dat::base::Set* set, dat::base::Entity* entity){
  return entity->UID == set->active_entity->UID;
}

//Subfunction
int Set::compute_number_entity(dat::base::Set* set){
  int nb_entity = 0;
  //---------------------------

  nb_entity += set->list_entity.size();

  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    nb_entity += compute_number_entity(subset);
  }

  //---------------------------
  return nb_entity;
}
int Set::compute_number_point(dat::base::Set* set){
  int nb_point = 0;
  //---------------------------

  // Add the points in the current set
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    utl::type::Data* data = entity->get_data();
    nb_point += data->size;
  }

  // Recursively add points from nested subsets
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    nb_point += compute_number_point(subset);
  }

  //---------------------------
  return nb_point;
}
bool Set::is_set_empty(dat::base::Set* set){
  int nb_entity = 0;
  //---------------------------

  nb_entity += set->list_entity.size();
  if(nb_entity > 0) return false;

  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    nb_entity += compute_number_entity(subset);
  }
  if(nb_entity > 0) return false;

  //---------------------------
  return true;
}

}
