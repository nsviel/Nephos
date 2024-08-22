#include "Element.h"

#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>


namespace dat::gph{

//Constructor / Destructor
Element::Element(dat::gph::Node* node_graph){
  //---------------------------

  dat::elm::Node* node_element = node_graph->get_node_element();

  this->gph_struct = node_graph->get_gph_struct();
  this->dat_set = node_element->get_dat_set();
  this->gph_selection = node_graph->get_gph_selection();

  //---------------------------
}
Element::~Element(){}

//Main function
void Element::remove_entity(dat::base::Set* set, dat::base::Entity* entity){
  if(entity == nullptr) return;
  //---------------------------

  //Selection
  if(gph_struct->selection == entity){
    gph_selection->select_next_element();
  }

  //Remove
  dat_set->remove_entity(set, entity);

  //---------------------------
}
void Element::remove_active_entity(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------

  if(gph_struct->selection == set->active_entity){
    gph_selection->select_next_element();
  }

  dat_set->remove_active_entity(set);

  //---------------------------
}
void Element::remove_set(dat::base::Set* set){
  if(set == nullptr) return;
  //---------------------------

  // Check if the current set has the query entity
  while(set->list_entity.size() != 0){
    dat::base::Entity* entity = *set->list_entity.begin();
    this->remove_entity(set, entity);
    if(set == nullptr) say("coucou");
  }

  // Recursively call remove_entity_recursive for each nested set
  for(dat::base::Set* subset : set->list_subset){
    this->remove_set(subset);
  }

  //---------------------------
}

}
