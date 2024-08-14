#include "Node.h"

#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::elm{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  //---------------------------

  //Dependancy
  this->node_core = node_data->get_node_core();
  this->node_vulkan = node_data->get_node_vulkan();

  //Child
  this->dat_struct = new dat::elm::Structure();
  this->dat_uid = new dat::elm::UID();
  this->dat_set = new dat::elm::Set(this);
  this->dat_entity = new dat::elm::Entity(this);
  this->dat_glyph = new dat::elm::Glyph(this);
  this->dat_image = new dat::elm::Image(this);

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
