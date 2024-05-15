#include "Node.h"

#include <Application/Node.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>

#include <image/IconsFontAwesome6.h>


namespace sce{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  //Dependancy
  this->node_engine = node_app->get_node_engine();
  this->node_vulkan = node_engine->get_node_vulkan();

  //Child
  this->sce_init = new sce::Init(this);
  this->sce_module = new sce::Module(this);

  this->add_node_panel(sce_module);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  sce_module->init();
  sce_init->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  sce_module->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  sce_module->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  sce_module->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
