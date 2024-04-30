#include "Graph.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>


namespace dat{

//Constructor / Destructor
Graph::Graph(dat::Node* node_data){
  //---------------------------

  this->set_main = new dat::base::Set();
  this->dat_set = new dat::Set();

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::init(){
  //---------------------------

  set_scene = dat_set->create_subset(set_main, "Scene");
  set_scene->is_suppressible = false;
  set_scene->is_open = false;

  set_graph = dat_set->create_subset(set_main, "Graph");
  set_graph->is_suppressible = false;

  //---------------------------
}
void Graph::loop(){
  //----------------------------

  dat_set->update_set(set_main);

  //----------------------------
}
void Graph::reset(){
  //---------------------------

  dat_set->reset_set(set_main);

  //---------------------------
}
void Graph::clean(){
  //---------------------------

  dat_set->remove_entity_all(set_main);

  //---------------------------
}

//Subfunction
void Graph::assign_UID(utl::type::Element* element){
  if(element == nullptr) return;
  //----------------------------

  if(element->UID == -1){
    element->UID = set_main->UID++;
  }

  //----------------------------
}

}
