#include "Set.h"

#include <Data/Element/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::elm{

//Constructor / Destructor
Set::Set(dat::elm::Node* node_element){
  //---------------------------

  this->dat_entity = new dat::elm::Entity(node_element);
  this->dat_uid = node_element->get_dat_uid();

  //---------------------------
}
Set::~Set(){}

//Set function
void Set::update_data(dat::base::Set* set){
  //---------------------------

  // Process entities within the current set
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), i);
    dat_entity->update_data(entity);
  }

  // Recursively process nested sets
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->update_data(subset);
  }

  //---------------------------
}
void Set::reset_set(dat::base::Set* set){
  //---------------------------

  //Reset own stuff
  set->pose = {};
  set->reset();

  //Reset all associated entities
  for(int j=0; j<set->list_entity.size(); j++){
    dat::base::Entity* entity = *next(set->list_entity.begin(), j);
    dat_entity->reset_pose(entity);
  }

  //Reset all associated subsets
  for(int i=0; i<set->list_subset.size(); i++){
    dat::base::Set* subset = *next(set->list_subset.begin(), i);
    this->reset_set(subset);
  }

  //---------------------------
}
void Set::visibility_set(dat::base::Set* set, bool value){
  if(!set) return;
  //---------------------------

  set->is_visible = value;

  for(dat::base::Entity* entity : set->list_entity){
    dat_entity->visibility_entity(entity, value);
  }

  // Recursively call remove for each nested set
  for(dat::base::Set* subset : set->list_subset){
    this->visibility_set(subset, value);
  }

  //If visible so parent set is too
  if(value && set->set_parent && !set->set_parent->is_visible){
    this->visibility_set(set->set_parent, value);
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
  subset->UID = dat_uid->generate_UID();
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
    dat::base::Set* subsubset = get_subset(subset, name);
    if(subsubset){
      return subsubset;
    }
  }

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

  // Check if the current set has the query entity
  for(int i=0; i<set->list_entity.size(); i++){
    dat::base::Entity* entity_set = *next(set->list_entity.begin(), i);

    if(entity_set->UID == entity->UID){
      //Check if active entity
      if(set->active_entity == entity) this->active_next_entity(set);

      //Remove from set list
      set->list_entity.remove(entity);
      set->nb_entity--;

      //Check if active entity agin
      if(set->active_entity == entity) set->active_entity = nullptr;

      //Effective remove
      dat_entity->remove_entity(entity);

      return;
    }
  }

  // Recursively call remove for each nested set
  for(dat::base::Set* subset : set->list_subset){
    this->remove_entity(subset, entity);
  }

  //---------------------------
}
void Set::remove_active_entity(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------

  this->remove_entity(set, set->active_entity);

  //---------------------------
}
void Set::remove_all_entity(dat::base::Set* set){
  //---------------------------

  // Check if the current set has the query entity
  auto it = set->list_entity.begin();
  while(it != set->list_entity.end()){
    dat::base::Entity* entity = *it;

    //Effective remove
    it = set->list_entity.erase(it);
    set->nb_entity--;
    dat_entity->remove_entity(entity);
  }

  // Recursively call remove_entity_recursive for each nested set
  for(dat::base::Set* subset : set->list_subset){
    this->remove_all_entity(subset);
  }

  //---------------------------
}
void Set::active_next_entity(dat::base::Set* set){
  //----------------------------

  //If no entities
  if(set->list_entity.size() == 0){
    set->active_entity = nullptr;
    return;
  }
  //If entity but previsouly selection not set
  else if(set->active_entity == nullptr){
    set->active_entity = *set->list_entity.begin();
    return;
  }
  //Else select next entity
  else{
    for(auto it = set->list_entity.begin(); it != set->list_entity.end(); ++it){
      dat::base::Entity* entity = *it;

      if(set->active_entity->UID == entity->UID){
        auto next_it = std::next(it);

        // If at the end of the list, cycle back to the beginning
        if(next_it == set->list_entity.end()){
          set->active_entity = *set->list_entity.begin();
        }else{
          set->active_entity = *next_it;
        }

        return;
      }
    }
  }

  //----------------------------
}
void Set::active_entity(dat::base::Set* set, dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  set->active_entity = entity;

  //---------------------------
}
bool Set::is_entity_active(dat::base::Set* set, dat::base::Entity* entity){
  //---------------------------

  if(entity == nullptr) return false;
  if(set == nullptr) return false;
  if(set->active_entity == nullptr) return false;

  bool is_active = entity->UID == set->active_entity->UID;

  //---------------------------
  return is_active;
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
    utl::base::Data* data = &entity->data;
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
