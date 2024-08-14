#include "Node.h"

#include <Core/Namespace.h>
#include <RealSense/Namespace.h>
#include <IO/Namespace.h>
#include <Data/Namespace.h>
#include <Importer/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rlx{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->node_io = node_engine->get_node_io();
  this->node_profiler = node_engine->get_node_profiler();
  this->node_data = node_engine->get_node_data();
  //this->rlx_class = new rlx::Class();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  io::imp::Node* node_importer = node_io->get_node_importer();
  io::imp::Importer* io_importer = node_importer->get_io_importer();
  //---------------------------

  //io_importer->insert_importer(new k4n::playback::Importer(this));



  //---------------------------
}
void Node::init(){
  //---------------------------

  //rlx_class->capture();

  //---------------------------
}



}
