#include "Node.h"

#include <Dynamic/Sensor/Namespace.h>
#include <Kinect/Namespace.h>
#include <Core/Namespace.h>
#include <IO/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace k4n{

//Constructor / Destructor
Node::Node(dyn::sen::Node* node_sensor){
  //---------------------------

  //Dependancy
  this->node_core = node_sensor->get_node_core();
  this->node_io = node_core->get_node_io();
  this->node_data = node_core->get_node_data();
  this->node_processing = node_sensor->get_node_processing();

  //Child
  this->k4n_structure = new k4n::Structure();
  this->k4n_connection = new k4n::capture::Connection(this);

  //Importer
  io::imp::Node* node_importer = node_io->get_node_importer();
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
