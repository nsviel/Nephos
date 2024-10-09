#include "Node.h"

#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::gph{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  utl::gui::Panel* dat_panel = add_panel("Graph", ICON_FA_FILE, true);
  //---------------------------

  //Dependancy
  this->node_element = node_data->get_node_element();
  this->node_vulkan = node_data->get_node_vulkan();

  //Child
  this->gph_struct = new dat::gph::Structure();
  this->gph_publisher = new dat::gph::Publisher();
  this->gph_graph = new dat::gph::Graph(this);
  this->gph_selection = new dat::gph::Selection(this);
  this->gph_element = new dat::gph::Element(this);
  this->gui_graph = new dat::gph::gui::Panel(this, &dat_panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  gph_graph->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  gph_graph->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  gph_graph->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_graph->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  gph_graph->reset();

  //---------------------------
}


}
