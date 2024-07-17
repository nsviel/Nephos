#include "Graph.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>
#include <Dynamic/Namespace.h>


namespace dat{

//Constructor / Destructor
Graph::Graph(dat::Node* node_data){
  //---------------------------

  this->node_data = node_data;
  this->dat_struct = node_data->get_dat_struct();
  this->dat_set = node_data->get_dat_set();

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::init(){
  dat::Glyph* dat_glyph = node_data->get_dat_glyph();
  //---------------------------

  //Background permanent elements
  dat::base::Set* set_scene = dat_set->create_subset(&dat_struct->set_main, "Scene");
  set_scene->is_suppressible = false;
  set_scene->is_open = false;
  set_scene->is_locked = true;

  dat_glyph->insert_glyph(set_scene, new dat::glyph::grid::Grid());
  dat_glyph->insert_glyph(set_scene, new dat::glyph::world::Axis());

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

  dat_set->reset_set(&dat_struct->set_main);

  //---------------------------
}
void Graph::clean(){
  //---------------------------

  dat_set->remove_all_entity(&dat_struct->set_main);

  //---------------------------
}

//Accesseur
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
