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

//Subset function
void Set::add_subset(utl::type::Set* subset){
  //---------------------------

  subset->set_parent = this;
  list_subset.push_back(subset);
  this->nb_set++;
  //this->select_next_entity();
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
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);
    entity->set_visibility(value);
  }

  //---------------------------
}




}
