#include "Graph.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>
#include <Dynamic/Namespace.h>


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
  set_graph->player = new dyn::base::Player(set_graph);
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
void Graph::select_element(utl::base::Element* element){
  if(element->is_selectable == false) return;
  //----------------------------

  dat_struct->selection = element;

  //If an entity, make it active
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    dat_set->active_entity(entity->set_parent, entity);
  }

  //----------------------------
}
void Graph::remove_selected_element(){
  //----------------------------


  //----------------------------
}
void Graph::select_next_element(){
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
void Graph::assign_UID(utl::base::Element* element){
  if(element == nullptr) return;
  //----------------------------

  if(element->UID == -1){
    element->UID = dat_struct->UID++;
  }

  //----------------------------
}
utl::base::Element* Graph::get_selected_element(){
  return dat_struct->selection;
}
dat::base::Entity* Graph::get_selected_entity(){
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
dat::base::Set* Graph::get_selected_set(){
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
