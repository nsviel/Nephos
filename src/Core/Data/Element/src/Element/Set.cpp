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
void Set::update_data(std::shared_ptr<dat::base::Set> set){
  //---------------------------

  // Process entities within the current set
  for(auto& entity : set->list_entity){
    dat_entity->update_data(entity);
  }

  // Recursively process nested sets
  for(auto& subset : set->list_subset){
    this->update_data(subset);
  }

  //---------------------------
}
void Set::reset_set(std::shared_ptr<dat::base::Set> set){
  //---------------------------

  //Reset own stuff
  set->pose = {};
  set->reset();

  //Reset all associated entities
  for(auto& entity : set->list_entity){
    dat_entity->reset_pose(entity);
  }

  //Reset all associated subsets
  for(auto& subset : set->list_subset){
    this->reset_set(subset);
  }

  //---------------------------
}
void Set::visibility_set(std::shared_ptr<dat::base::Set> set, bool value){
  if(!set) return;
  //---------------------------

  set->is_visible = value;

  for(std::shared_ptr<dat::base::Entity> entity : set->list_entity){
    dat_entity->visibility_entity(entity, value);
  }

  // Recursively call remove for each nested set
  for(auto& subset : set->list_subset){
    this->visibility_set(subset, value);
  }

  //If visible so parent set is too
  auto set_parent = set->set_parent.lock();
  if(value && set_parent && !set_parent->is_visible){
    this->visibility_set(set_parent, value);
  }

  //---------------------------
}

//Subset function
void Set::add_subset(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Set> subset){
  //---------------------------

  subset->set_parent = set;
  set->list_subset.push_back(subset);
  set->nb_subset++;

  if(subset->nb_entity != 0){
    set->active_subset = subset;
  }

  //---------------------------
}
void Set::remove_subset(std::shared_ptr<dat::base::Set> subset){
  if(!subset) return;
  //---------------------------

  std::shared_ptr<dat::base::Set> set = subset->set_parent.lock();
  set->list_subset.remove(subset);

  //delete subset;
  //subset = nullptr;

  //---------------------------
}
std::shared_ptr<dat::base::Set> Set::create_subset(std::shared_ptr<dat::base::Set> set, std::string name){
  if(!set) return nullptr;
  //---------------------------

  std::shared_ptr<dat::base::Set> subset = std::make_shared<dat::base::Set>();
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
std::shared_ptr<dat::base::Set> Set::get_subset(std::shared_ptr<dat::base::Set> set, std::string name){
  //---------------------------

  for(auto& subset : set->list_subset){
    if(subset->name == name){
      return subset;
    }
    std::shared_ptr<dat::base::Set> subsubset = get_subset(subset, name);
    if(subsubset){
      return subsubset;
    }
  }

  //---------------------------
  return nullptr;
}
std::shared_ptr<dat::base::Set> Set::get_or_create_subset(std::shared_ptr<dat::base::Set> set, std::string name){
  //---------------------------

  for(auto& subset_in_list : set->list_subset){
    if(subset_in_list->name == name){
      return subset_in_list;
    }
  }

  std::shared_ptr<dat::base::Set> subset = create_subset(set, name);

  //---------------------------
  return subset;
}

//Entity function
void Set::insert_entity(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity){
  if(!set || !entity) return;
  //---------------------------

  entity->set_parent = set;
  set->list_entity.push_back(entity);
  set->nb_entity++;
  this->active_entity(set, entity);

  //---------------------------
}
void Set::remove_entity(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity){
  if(!entity) return;
  //---------------------------

  // Check if the set has the entity to be removed
  auto it = std::find_if(set->list_entity.begin(), set->list_entity.end(),
    [&entity](const std::shared_ptr<dat::base::Entity>& e){
      return e->UID == entity->UID;
    });

  if(it != set->list_entity.end()){
    // If entity is found in the set
    std::shared_ptr<dat::base::Entity> found_entity = *it;

    // Check if the found entity is the active entity
    auto active_entity = set->active_entity.lock();
    if(active_entity && active_entity == found_entity){
      this->active_next_entity(set);
    }

    // Remove from set list
    set->list_entity.erase(it);
    set->nb_entity--;

    // Check if the removed entity was the active one
    if(active_entity == found_entity){
      set->active_entity.reset();
    }

    // Effectively remove the entity
    dat_entity->remove_entity(found_entity);
  }

  // Recursively call remove for each nested set
  for(auto& subset : set->list_subset){
    this->remove_entity(subset, entity);
  }

  //Remove if empty
  if(set->is_suppressible && set->list_subset.empty() && set->list_entity.empty()){
    this->remove_subset(set);
  }

  //---------------------------
}
void Set::remove_active_entity(std::shared_ptr<dat::base::Set> set){
  if(!set) return;
  //---------------------------

  std::shared_ptr<dat::base::Entity> entity = set->active_entity.lock();
  this->remove_entity(set, entity);

  //---------------------------
}
void Set::remove_all_entity(std::shared_ptr<dat::base::Set> set){
  //---------------------------

  // Check if the current set has the query entity
  auto it = set->list_entity.begin();
  while(it != set->list_entity.end()){
    std::shared_ptr<dat::base::Entity> entity = *it;

    //Effective remove
    it = set->list_entity.erase(it);
    set->nb_entity--;
    dat_entity->remove_entity(entity);
  }

  // Recursively call remove_entity_recursive for each nested set
  for(auto& subset : set->list_subset){
    this->remove_all_entity(subset);
  }

  //---------------------------
}
void Set::active_next_entity(std::shared_ptr<dat::base::Set> set){
  auto set_active = set->active_entity.lock();
  //----------------------------

  //If no entities
  if(set->list_entity.empty()){
    set->active_entity.reset();
    return;
  }
  //If entity but previsouly selection not set
  else if(!set_active){
    set->active_entity = *set->list_entity.begin();
    return;
  }
  //Else select next entity
  else{
    for(auto it = set->list_entity.begin(); it != set->list_entity.end(); ++it){
      if(set_active->UID == (*it)->UID){
        auto next_it = std::next(it);

        // If at the end of the list, cycle back to the beginning
        if(next_it == set->list_entity.end()){
          set->active_entity = *set->list_entity.begin();
        } else {
          set->active_entity = *next_it;
        }

        return;
      }
    }
  }

  //----------------------------
}
void Set::active_entity(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity){
  if(!entity) return;
  //---------------------------

  set->active_entity = entity;

  //---------------------------
}
bool Set::is_entity_active(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity){
  auto active_entity = set->active_entity.lock();
  //---------------------------

  if(!entity) return false;
  if(!set) return false;
  if(!active_entity) return false;

  bool is_active = entity->UID == active_entity->UID;

  //---------------------------
  return is_active;
}

//Subfunction
int Set::compute_number_entity(std::shared_ptr<dat::base::Set> set){
  int nb_entity = 0;
  //---------------------------

  nb_entity += set->list_entity.size();

  for(auto& subset : set->list_subset){
    nb_entity += compute_number_entity(subset);
  }

  //---------------------------
  return nb_entity;
}
int Set::compute_number_point(std::shared_ptr<dat::base::Set> set){
  int nb_point = 0;
  //---------------------------

  // Add the points in the current set
  for(auto& entity : set->list_entity){
    utl::base::Data& data = *entity->data;
    nb_point += data.size;
  }

  // Recursively add points from nested subsets
  for(auto& subset : set->list_subset){
    nb_point += compute_number_point(subset);
  }

  //---------------------------
  return nb_point;
}
bool Set::is_set_empty(std::shared_ptr<dat::base::Set> set){
  int nb_entity = 0;
  //---------------------------

  nb_entity += set->list_entity.size();
  if(nb_entity > 0) return false;

  for(auto& subset : set->list_subset){
    nb_entity += compute_number_entity(subset);
  }
  if(nb_entity > 0) return false;

  //---------------------------
  return true;
}

}
