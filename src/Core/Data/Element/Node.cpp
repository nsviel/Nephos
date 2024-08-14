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

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_graph = node_engine->get_node_graph();

  //Child
  this->dat_struct = new dat::Structure();
  this->dat_set = new dat::element::Set(this);
  this->dat_entity = new dat::element::Entity(this);
  this->dat_glyph = new dat::Glyph(this);
  this->dat_image = new dat::element::Image(this);

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
