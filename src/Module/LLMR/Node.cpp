#include "Node.h"

#include <Module/Namespace.h>
#include <Core/Namespace.h>
#include <Utility/Namespace.h>
#include <LLMR/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace llmr{

//Constructor / Destructor
Node::Node(mod::Node* node_module){
  utl::gui::Panel* panel = add_panel("LLMR", ICON_FA_FILM, true);
  //---------------------------

  //Dependancy
  this->node_core = node_module->get_node_core();
  this->node_data = node_core->get_node_data();

  //Child
  this->llmr_interface = new llmr::Interface();
  this->gui_panel = new llmr::gui::Panel(this, &panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  llmr_interface->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_panel->run_panel();

  //---------------------------
}

}
