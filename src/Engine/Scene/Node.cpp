#include "Node.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Scene/Namespace.h>
#include <Glyph/Namespace.h>
#include <Loader/Namespace.h>
#include <Module/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace sce{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();

  //Child
  this->node_glyph = new gly::Node(this);
  this->node_module = new eng::module::Node(node_engine);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_module->config();
  node_glyph->init();
  node_module->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_module->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_module->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_module->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
