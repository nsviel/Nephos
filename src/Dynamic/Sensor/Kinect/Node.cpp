#include "Node.h"

#include <Core/Namespace.h>
#include <Kinect/Namespace.h>
#include <IO/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <Importer/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace k4n{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  //Dependancy
  this->node_core = node_core;
  this->node_io = node_core->get_node_io();
  this->node_data = node_core->get_node_data();
  this->node_dynamic = node_core->get_node_dynamic();
  io::imp::Node* node_importer = node_io->get_node_importer();

  //Child
  this->k4n_structure = new k4n::Structure();
  this->k4n_connection = new k4n::capture::Connection(this);

  //Importer
  io::imp::Importer* io_importer = node_importer->get_io_importer();
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
