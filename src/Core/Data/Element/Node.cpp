#include "Node.h"

#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <Graph/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------
sayHello();
  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();

sayHello();
  //Child
  this->dat_struct = new dat::Structure();
  this->dat_uid = new dat::graph::UID(this);
  this->dat_set = new dat::element::Set(this);
  this->dat_entity = new dat::element::Entity(this);
  this->dat_glyph = new dat::Glyph(this);
  this->dat_image = new dat::element::Image(this);

sayHello();
    this->node_graph = node_engine->get_node_graph();
sayHello();
  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::loop(){
  //---------------------------


  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}
void Node::gui(){
  //---------------------------



  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
