#include "Node.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Loader/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/Namespace.h>
#include <image/IconsFontAwesome6.h>
#include <Module/Node.h>


namespace k4n{

//Constructor / Destructor
Node::Node(mod::Node* node_module){
  //---------------------------

  //Dependancy
  this->node_engine = node_module->get_node_engine();
  this->node_loader = node_engine->get_node_loader();
  this->node_profiler = node_engine->get_node_profiler();
  this->node_data = node_engine->get_node_data();
  this->node_radio = node_module->get_node_radio();

  //Child
  this->k4n_connection = new k4n::capture::Connection(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  ldr::Format* ldr_format = node_loader->get_ldr_format();
  //---------------------------

  ldr_format->insert_importer(new k4n::playback::Importer(this));
  //k4n_connection->start_thread();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  k4n_connection->stop_thread();

  //---------------------------
}



}
