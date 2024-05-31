#include "Selection.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>
#include <Dynamic/Namespace.h>


namespace dat{

//Constructor / Destructor
Selection::Selection(dat::Node* node_data){
  //---------------------------

  this->dat_struct = node_data->get_dat_struct();
  this->dat_set = node_data->get_dat_set();

  //---------------------------
}
Selection::~Selection(){}

//Main function
void Selection::select_element(utl::base::Element* element){
  if(element->is_selectable == false) return;
  //----------------------------

  dat_struct->selection = element;

  //If an entity, make it active
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    dat_set->active_entity(entity->set_parent, entity);
  }

  //----------------------------
}
void Selection::select_next_element(){
  utl::base::Element* element = dat_struct->selection;
  if(element == nullptr) return;
  //----------------------------

  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    if(set->list_entity.size() != 0){
      dat_set->active_next_entity(set);
      dat_struct->selection = set->active_entity;
      return;
    }else if(set->list_subset.size() != 0){
      dat_struct->selection = *set->list_subset.begin();
    }
  }
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    dat_set->active_next_entity(entity->set_parent);
    dat_struct->selection = entity->set_parent->active_entity;
  }

  //----------------------------
}

//Accesseur
utl::base::Element* Selection::get_selected_element(){
  return dat_struct->selection;
}
dat::base::Entity* Selection::get_selected_entity(){
  utl::base::Element* element = dat_struct->selection;
  //---------------------------

  dat::base::Entity* entity;
  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    entity = set->active_entity;
  }else{
    entity = dynamic_cast<dat::base::Entity*>(element);
  }

  //---------------------------
  return entity;
}
dat::base::Set* Selection::get_selected_set(){
  utl::base::Element* element = dat_struct->selection;
  //---------------------------

  dat::base::Set* set;
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    set = entity->set_parent;
  }else{
    set = dynamic_cast<dat::base::Set*>(element);
  }

  //---------------------------
  return set;
}

}
