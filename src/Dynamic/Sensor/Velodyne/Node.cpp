#include "Node.h"

#include <Dynamic/Sensor/Namespace.h>
#include <Velodyne/Namespace.h>
#include <Core/Namespace.h>
#include <IO/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace vld{

//Constructor / Destructor
Node::Node(dyn::sen::Node* node_sensor){
  //---------------------------

  core::Node* node_core = node_sensor->get_node_core();
  this->node_data = node_core->get_node_data();
  this->node_io = node_core->get_node_io();

  this->vld_struct = new vld::Structure();
  this->vld_capture = new vld::main::Capture(this);
  this->vld_playback = new vld::main::Playback(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  io::imp::Node* node_importer = node_io->get_node_importer();
  io::imp::Importer* io_importer = node_importer->get_io_importer();
  //---------------------------

  io_importer->insert_importer(new vld::utils::Importer(this));

  //---------------------------
}
void Node::init(){
  //---------------------------

  vld_capture->init();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vld_playback->stop_playback();
  vld_capture->clean();

  //---------------------------
}

}
