#include "Node.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/src/Device/Swarm.h>
#include <Engine/Capture/K4N/src/Device/Connection.h>


namespace eng::k4n{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->k4n_swarm = new eng::k4n::dev::Swarm(this);
  this->k4n_connection = new eng::k4n::dev::Connection(this);
  //this->k4a_cloud = new eng::k4n::data::Cloud(engine);

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

  k4n_connection->refresh_connected_dev();
  //rnd_kinect->run_panel();
  //rnd_stream->run_panel();

  //---------------------------
}


}
