#include "Node.h"

#include <Application/Node.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Module/Node.h>
#include <image/IconsFontAwesome6.h>


namespace sce{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  //Dependancy
  this->node_engine = node_app->get_node_engine();
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_module = new mod::Node(node_engine);

  //Child
  this->sce_init = new sce::Init(this);

  this->add_node_panel(node_module);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_module->init();
  sce_init->init();

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
