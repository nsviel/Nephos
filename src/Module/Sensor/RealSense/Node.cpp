#include "Node.h"

#include <Engine/Namespace.h>
#include <RealSense/Namespace.h>
#include <IO/Namespace.h>
#include <Data/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rsx{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_loader = node_engine->get_node_loader();
  this->node_profiler = node_engine->get_node_profiler();
  this->node_data = node_engine->get_node_data();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  ldr::io::Importer* ldr_importer = node_loader->get_ldr_importer();
  //---------------------------

  //ldr_importer->insert_importer(new k4n::playback::Importer(this));

  //---------------------------
}
void Node::init(){
  //---------------------------


  //---------------------------
}



}
