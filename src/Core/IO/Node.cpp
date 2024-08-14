#include "Node.h"
#include "Namespace.h"


namespace io{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_importer = new io::imp::Node(node_core);
  this->node_exporter = new io::exp::Node(node_core);
  this->node_transfor = new io::trf::Node(node_core);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_importer->init();
  node_exporter->init();
  node_transfor->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_importer->gui();
  node_exporter->gui();
  node_transfor->gui();

  //---------------------------
}

}
