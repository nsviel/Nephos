#include "Node.h"

#include <Application/Node.h>
#include <Core/Namespace.h>
#include <Scene/Namespace.h>


namespace sce{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  //Dependancy
  this->node_core = node_app->get_node_core();

  //Child
  this->sce_struct = new sce::Structure();
  this->sce_import = new sce::Import(this);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  sce_import->init();

  //---------------------------
}


}
