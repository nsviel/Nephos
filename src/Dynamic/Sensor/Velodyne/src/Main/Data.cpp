#include "Data.h"

#include <Velodyne/Namespace.h>
#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <Data/Node.h>
#include <Importer/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Data::Data(vld::Node* node_vld){
  //---------------------------

  eng::Node* node_engine = node_vld->get_node_engine();
  dat::Node* node_data = node_engine->get_node_data();
  io::Node* node_io = node_engine->get_node_io();
  dat::graph::Node* node_graph = node_data->get_node_graph();
  io::imp::Node* node_importer = node_io->get_node_importer();

  this->node_engine = node_vld->get_node_engine();
  this->vld_struct = node_vld->get_vld_struct();
  this->dat_graph = node_graph->get_dat_graph();
  this->io_loader = node_importer->get_io_importer();
  this->dat_set = node_data->get_dat_set();
  this->dat_entity = node_data->get_dat_entity();

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::create_object(){
  if(vld_struct->data.object != nullptr) return;
  //---------------------------

  vld_struct->data.object = new dat::base::Object();
  vld_struct->data.object->name = "capture_1";
  vld_struct->data.object->data.name = "velodyne::capture::data";
  vld_struct->data.object->data.topology.type = utl::topology::POINT;
  vld_struct->data.object->data.nb_data_max = 1000000;
  vld_struct->data.object->pose.model[2][3] = 1;
  dat_entity->init_entity(vld_struct->data.object);

  dat::base::Set* set_scene = dat_graph->get_set_graph();
  dat::base::Set* set_capture = dat_set->get_or_create_subset(set_scene, "Data");
  dat_set->insert_entity(set_capture, vld_struct->data.object);

  //---------------------------
}

}
