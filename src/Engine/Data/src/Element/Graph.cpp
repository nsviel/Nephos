#include "Graph.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>


namespace dat{

//Constructor / Destructor
Graph::Graph(dat::Node* node_data){
  //---------------------------

  this->dat_struct = node_data->get_data_struct();
  this->dat_set = node_data->get_data_set();

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::init(){
  //---------------------------

  //Background permanent elements
  dat::base::Set* set_scene = dat_set->create_subset(&dat_struct->set_main, "Scene");
  set_scene->is_suppressible = false;
  set_scene->is_open = false;

  //Engine active elements
  dat::base::Set* set_graph = dat_set->create_subset(&dat_struct->set_main, "Graph");
  set_graph->is_suppressible = false;
  dat_struct->selection = set_graph;

  //---------------------------
}
void Graph::loop(){
  //----------------------------

  dat_set->update_set(&dat_struct->set_main);

  //----------------------------
}
void Graph::reset(){
  //---------------------------

  dat_set->reset(&dat_struct->set_main);

  //---------------------------
}
void Graph::clean(){
  //---------------------------

  dat_set->remove_all_entity(&dat_struct->set_main);

  //---------------------------
}

//Subfunction
void Graph::select_element(utl::type::Element* element){
  if(element->is_selectable == false) return;
  //----------------------------

  dat_struct->selection = element;

  //If an entity, make it active
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    dat_set->active_entity(entity->set_parent, entity);
  }

  //----------------------------
}
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
utl::type::Element* Graph::get_selection(){
  return dat_struct->selection;
}


}
