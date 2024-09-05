#include "Node.h"

#include <Core/Namespace.h>
#include <IO/Namespace.h>


namespace io{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  //Dependancy
  this->node_data = node_core->get_node_data();
  this->node_engine = node_core->get_node_engine();

  //Child
  this->node_importer = new io::imp::Node(this);
  this->node_exporter = new io::exp::Node(this);
  this->node_format = new fmt::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_importer->init();
  node_format->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_importer->gui();
  node_exporter->gui();

  //---------------------------
}

}
