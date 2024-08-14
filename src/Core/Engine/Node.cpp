#include "Node.h"
#include "Namespace.h"


namespace eng_{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->node_camera = new cam::Node(node_engine);
  this->node_control = new ctl::Node(node_engine);
  this->node_renderer = new rnd::Node(node_engine);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_camera->init();
  node_renderer->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_camera->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_camera->gui();
  node_renderer->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_camera->reset();

  //---------------------------
}

}
