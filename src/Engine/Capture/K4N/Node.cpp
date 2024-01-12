#include "Node.h"

#include <Engine/Engine.h>


namespace k4n{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->k4a_swarm = new k4n::truc::Swarm(engine);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  k4a_swarm->manage_no_device();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  k4a_swarm->refresh_connected_device();
  k4a_swarm->draw_all_clouds();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  k4a_swarm->reset_all_device();

  //---------------------------
}


}
