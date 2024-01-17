#include "Node.h"

#include <Engine/Engine.h>


namespace k4n{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->k4n_swarm = new k4n::dev::Swarm(engine);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  k4n_swarm->init_scene();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  k4n_swarm->refresh_connected_sensor();
  k4n_swarm->draw_all_clouds();

  //---------------------------
}


}
