#include "Graph.h"

#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>


namespace dat::gph{

//Constructor / Destructor
Graph::Graph(dat::gph::Node* node_graph){
  //---------------------------

  dat::elm::Node* node_element = node_graph->get_node_element();

  this->dat_glyph = node_element->get_dat_glyph();
  this->gph_struct = node_graph->get_gph_struct();
  this->dat_set = node_element->get_dat_set();

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::init(){
  //---------------------------

  gph_struct->set_main = std::make_shared<dat::base::Set>();

  //Background permanent elements
  std::shared_ptr<dat::base::Set> set_scene = dat_set->create_subset(gph_struct->set_main, "Scene");
  set_scene->is_suppressible = false;
  set_scene->is_open = false;
  set_scene->is_locked = true;

  dat_glyph->insert_glyph(set_scene, std::make_shared<dat::glyph::grid::Grid>());
  dat_glyph->insert_glyph(set_scene, std::make_shared<dat::glyph::world::Axis>());

  //Engine active elements
  std::shared_ptr<dat::base::Set> set_graph = dat_set->create_subset(gph_struct->set_main, "Graph");
  set_graph->is_suppressible = false;
  gph_struct->selection = set_graph;

  //---------------------------
}
void Graph::loop(){
  //----------------------------

  dat_set->update_data(gph_struct->set_main);

  //----------------------------
}
void Graph::reset(){
  //---------------------------

  dat_set->reset_set(gph_struct->set_main);

  //---------------------------
}
void Graph::clean(){
  //---------------------------

  dat_set->remove_all_entity(gph_struct->set_main);

  //---------------------------
}

//Accesseur
std::shared_ptr<dat::base::Set> Graph::get_set_main(){
  return gph_struct->set_main;
}
std::shared_ptr<dat::base::Set> Graph::get_set_graph(){
  //----------------------------

  std::shared_ptr<dat::base::Set> set = dat_set->get_subset(gph_struct->set_main, "Graph");

  //----------------------------
  return set;
}
std::shared_ptr<dat::base::Set> Graph::get_set_scene(){
  //----------------------------

  std::shared_ptr<dat::base::Set> set = dat_set->get_subset(gph_struct->set_main, "Scene");

  //----------------------------
  return set;
}

}
