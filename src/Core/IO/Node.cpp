#include "Node.h"

#include <Core/Namespace.h>
#include <Importer/Namespace.h>
#include <Exporter/Namespace.h>


namespace io{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->node_importer = new io::imp::Node(node_engine);
  this->node_exporter = new io::exp::Node(node_engine);

  //---------------------------
}
Node::~Node(){}

}
