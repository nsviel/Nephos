#include "Node.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Capture/Namespace.h>
#include <Loader/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace k4n{

//Constructor / Destructor
Node::Node(cap::Node* node_capture){
  //---------------------------

  //Dependancy
  this->node_engine = node_capture->get_node_engine();
  this->node_loader = node_engine->get_node_loader();
  this->node_profiler = node_capture->get_node_profiler();
  this->node_data = node_engine->get_node_data();
  this->node_radio = new rad::Node(node_engine);

  //Child
  this->k4n_struct = new k4n::structure::K4N();
  this->k4n_swarm = new k4n::dev::Swarm(this);
  this->k4n_connection = new k4n::capture::Connection(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  ldr::Format* ldr_format = node_loader->get_format();
  //---------------------------

  ldr_format->insert_importer(new k4n::playback::Importer(this));

  //---------------------------
}
void Node::init(){
  //---------------------------

  k4n_connection->start_thread();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  k4n_swarm->manage_connected_device();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  k4n_swarm->close_all_master();

  //---------------------------
}


}
