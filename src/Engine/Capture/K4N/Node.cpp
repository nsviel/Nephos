#include "Node.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/Namespace.h>


namespace eng::k4n{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->k4n_swarm = new eng::k4n::dev::Swarm(this);
  this->k4n_connection = new eng::k4n::dev::Connection(this);
  this->gui_device = new eng::k4n::gui::Device(this, &show_gui);
  this->gui_stream = new eng::k4n::gui::Stream(this, &show_gui);

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

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_device->run_panel();
  gui_stream->run_panel();

  //---------------------------
}


}
