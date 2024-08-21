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

  if(gph_struct->selection == entity){
    gph_selection->select_next_element();
  }

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

}
