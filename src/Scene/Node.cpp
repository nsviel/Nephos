#include "Node.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Kinect/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace sce{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();

  //Child
  this->node_kinect = new k4n::Node(node_engine);
  this->sce_init = new sce::Init(this);

  this->add_node_panel(node_kinect);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_kinect->config();
  node_kinect->init();
  sce_init->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  //node_kinect->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  //node_kinect->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  //node_kinect->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
