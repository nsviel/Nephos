#include "Selection.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>
#include <Dynamic/Namespace.h>


namespace dat{

//Constructor / Destructor
Selection::Selection(dat::Node* node_data){
  //---------------------------

  this->dat_graph = node_data->get_dat_graph();
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
  dat::base::Set* set_graph = dat_graph->get_set_graph();
  //----------------------------

  //If set
  if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    // Handling selection within a set
    if(!set->list_entity.empty()){
      dat_struct->selection = *set->list_entity.begin(); // Select first entity in the set
      return;
    }else if(!set->list_subset.empty()){
      dat_struct->selection = *set->list_subset.begin(); // Select first subset in the set
      return;
    }else{
      // If no entities or subsets in the current set, move up the hierarchy
      dat::base::Set* set_parent = set->set_parent;
      auto it = std::find(set_parent->list_subset.begin(), set_parent->list_subset.end(), set);
      if(it != set_parent->list_subset.end() && ++it != set_parent->list_subset.end()){
        // Select the next subset in the parent set
        dat_struct->selection = *it;
        return;
      }else{
        dat_struct->selection = set_graph; // Loop back to the root if no next element is found
        return;
      }
    }
  }
  //If entity
  else if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    // Handling selection within an entity
    dat::base::Set* set_parent = entity->set_parent;
    auto it = std::find(set_parent->list_entity.begin(), set_parent->list_entity.end(), entity);
    if(it != set_parent->list_entity.end() && ++it != set_parent->list_entity.end()){
      // Select the next entity in the parent set
      dat_struct->selection = *it;
      return;
    }else{
      // If no next entity in the parent set, move up the hierarchy
      if(set_parent->list_subset.size() > 0){
      dat_struct->selection = *set_parent->list_subset.begin();
      return;
      }

      dat_struct->selection = set_graph; // Loop back to the root if no next element is found
      return;
    }
  }
  else if(element == nullptr){
    dat_struct->selection = set_graph; // Start from the root if no current selection
    return;
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
