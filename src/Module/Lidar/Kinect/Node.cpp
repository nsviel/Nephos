#include "Node.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Loader/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace k4n{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_loader = node_engine->get_node_loader();
  this->node_profiler = node_engine->get_node_profiler();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();

  //Child
  this->k4n_structure = new k4n::Structure();
  this->k4n_connection = new k4n::capture::Connection(this);
  this->k4n_config = new k4n::utils::Configuration(this);

  //Importer
  ldr::io::Importer* ldr_importer = node_loader->get_ldr_importer();
  ldr_importer->insert_importer(new k4n::playback::Importer(this));

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  k4n_config->make_default_configuration();
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
