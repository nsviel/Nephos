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
void Element::remove_entity(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity){
  if(!set || !entity) return;
  //---------------------------

  //Check for selection
  if(gph_struct->selection.lock() == entity){
    gph_selection->select_next_element();
  }

  //Remove entity
  dat_set->remove_entity(set, entity);

  //---------------------------
}
void Element::remove_active_entity(std::shared_ptr<dat::base::Set> set){
  if(!set) return;
  //---------------------------

  //Check for selection
  if(gph_struct->selection.lock() == set->active_entity.lock()){
    gph_selection->select_next_element();
  }

  //Remove set active entity
  dat_set->remove_active_entity(set);

  //---------------------------
}
void Element::remove_set(std::shared_ptr<dat::base::Set> set){
  if(!set) return;
  //---------------------------

  // Check if the current set has the query entity
  while(set->list_entity.size() != 0){
    std::shared_ptr<dat::base::Entity> entity = *set->list_entity.begin();
    this->remove_entity(set, entity);
  }

  // Recursively call remove_entity_recursive for each nested set
  std::vector<std::shared_ptr<dat::base::Set>> list_subset(set->list_subset.begin(), set->list_subset.end());
  for(auto& subset : list_subset){
    this->remove_set(subset);
  }

  //---------------------------
}

}
