#include "Node.h"

#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <Importer/Namespace.h>
#include <Exporter/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();
  this->node_importer = new io::imp::Node(node_engine);
  this->node_exporter = new io::exp::Node(node_engine);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------


  //---------------------------
}
void Node::gui(){
  //---------------------------


  //---------------------------
}

}
