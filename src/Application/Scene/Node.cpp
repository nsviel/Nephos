#include "Node.h"

#include <Application/Node.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace sce{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  //Dependancy
  this->node_engine = node_app->get_node_engine();
  this->node_kinect = new k4n::Node(node_engine);
  this->node_radio = new rad::Node(node_engine);

  //Child
  this->sce_init = new sce::Init(this);

  this->add_node_panel(node_kinect);
  this->add_node_panel(node_radio);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  sce_init->init();
  node_kinect->init();
  node_radio->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_radio->loop();
  node_kinect->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_kinect->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_radio->gui();
  node_kinect->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------



  //---------------------------
}


}
