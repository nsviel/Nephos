#include "Node.h"

#include <Core/Namespace.h>
#include <Graph/Namespace.h>
#include <IO/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::graph{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* dat_panel = add_panel("Graph", ICON_FA_FILE, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();

  //Child
  this->dat_struct = new dat::graph::Structure();
  this->dat_uid = new dat::graph::UID(this);
  this->dat_graph = new dat::graph::Graph(this);
  this->dat_selection = new dat::graph::Selection(this);
  this->gui_graph = new dat::graph::gui::Panel(this, &dat_panel->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  dat_graph->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  dat_graph->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  dat_graph->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_graph->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  dat_graph->reset();

  //---------------------------
}


}
