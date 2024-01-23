#include "Node.h"

#include <Engine/Engine.h>


namespace eng::k4n{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->k4n_swarm = new eng::k4n::dev::Swarm(engine);
  this->k4n_connection = new eng::k4n::dev::Connection(k4n_swarm);
  //this->rnd_kinect = new gui::kinect::Device(engine, &show_kinect, "Player");
  //this->rnd_stream = new gui::kinect::Stream(engine, &show_kinect, "Stream");

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
