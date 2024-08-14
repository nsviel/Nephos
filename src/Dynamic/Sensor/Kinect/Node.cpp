#include "Node.h"

#include <Core/Namespace.h>
#include <Kinect/Namespace.h>
#include <IO/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Element/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace k4n{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_io = node_engine->get_node_io();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();

  //Child
  this->k4n_structure = new k4n::Structure();
  this->k4n_connection = new k4n::capture::Connection(this);

  //Importer
  io::Importer* io_importer = node_io->get_io_importer();
  io_importer->insert_importer(new k4n::playback::Importer(this));

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  k4n_connection->start_thread();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  k4n_connection->stop_thread();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  k4n_connection->manage_connected_device();

  //---------------------------
}

}
