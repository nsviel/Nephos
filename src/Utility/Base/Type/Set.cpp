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

//Entity function
void Set::insert_entity(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  entity->set_parent = this;
  entity->update_pose();

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

//Subset function
void Set::add_subset(utl::type::Set* subset){
  //---------------------------

  subset->set_parent = this;
  list_subset.push_back(subset);
  this->nb_set++;
  this->select_next_entity();
  if(subset->nb_entity != 0){
    this->selected_set = subset;
  }

  //---------------------------
}
utl::type::Set* Set::create_subset(std::string name){
  //---------------------------

  utl::type::Set* subset = new utl::type::Set(name);
  subset->set_parent = this;
  subset->is_suppressible = true;

  this->nb_set++;
  this->selected_set = subset;
  this->list_subset.push_back(subset);

  //---------------------------
  return subset;
}
utl::type::Set* Set::get_subset(std::string name){
  //---------------------------

  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* subset = *next(list_subset.begin(),i);
    if(subset->name == name){
      return subset;
    }
  }

  std::cout<<"[error] Set not found ["<<name<<"]"<<std::endl;

  //---------------------------
  return nullptr;
}
utl::type::Set* Set::get_or_create_subset(std::string name){
  utl::type::Set* subset = nullptr;
  //---------------------------

  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* subset_in_list = *next(list_subset.begin(),i);
    if(subset_in_list->name == name){
      subset = subset_in_list;
      break;
    }
  }

  subset = create_subset(name);

  //---------------------------
  return subset;
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
int Set::compute_number_point(){
  int nb_point = 0;
  //---------------------------

  // Add the points in the current set
  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);
    utl::type::Data* data = entity->get_data();
    nb_point += data->point.size;
  }

  // Recursively add points from nested subsets
  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* subset = *next(list_subset.begin(), i);
    nb_point += subset->compute_number_point();
  }

  //---------------------------
  return nb_point;
}
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);
    entity->set_visibility(value);
  }

  //---------------------------
}




}
