#include "Graph.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>


namespace dat{

//Constructor / Destructor
Graph::Graph(dat::Node* node_data){
  //---------------------------

  this->dat_struct = node_data->get_struct();
  this->dat_set = node_data->get_set();

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::init(){
  //---------------------------

  dat::base::Set* set_scene = dat_set->create_subset(&dat_struct->set_main, "Scene");
  set_scene->is_suppressible = false;
  set_scene->is_open = false;

  dat::base::Set* set_graph = dat_set->create_subset(&dat_struct->set_main, "Graph");
  set_graph->is_suppressible = false;

  //---------------------------
}
void Graph::loop(){
  //----------------------------

  dat_set->update_set(&dat_struct->set_main);

  //----------------------------
}
void Graph::reset(){
  //---------------------------

  dat_set->reset_set(&dat_struct->set_main);

  //---------------------------
}
void Graph::clean(){
  //---------------------------

  dat_set->remove_entity_all(&dat_struct->set_main);

  //---------------------------
}

//Subfunction
void Graph::assign_UID(utl::type::Element* element){
  if(element == nullptr) return;
  //----------------------------

  if(element->UID == -1){
    element->UID = dat_struct->UID++;
  }

  //----------------------------
}
dat::base::Set* Graph::get_set_main(){
  return &dat_struct->set_main;
}
dat::base::Set* Graph::get_set_graph(){
  //----------------------------

  dat::base::Set* set = dat_set->get_subset(&dat_struct->set_main, "Graph");

  //----------------------------
  return set;
}
dat::base::Set* Graph::get_set_scene(){
  //----------------------------

  dat::base::Set* set = dat_set->get_subset(&dat_struct->set_main, "Scene");

  //----------------------------
  return set;
}


}
