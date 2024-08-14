#include "Node.h"

#include <Core/Namespace.h>
#include <Data/Namespace.h>
#include <IO/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::graph{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  utl::gui::Panel* dat_panel = add_panel("Graph", ICON_FA_FILE, true);
  //---------------------------

  //Dependancy
  this->node_data = node_data;
  this->node_core = node_data->get_node_core();
  this->node_vulkan = node_data->get_node_vulkan();

  //Child
  this->dat_struct = new dat::graph::Structure();
  this->dat_graph = new dat::graph::Graph(this);
  this->dat_selection = new dat::graph::Selection(this);
  this->gui_graph = new dat::graph::gui::Panel(this, &dat_panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
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
