#include "Data.h"

#include <Velodyne/Namespace.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Data::Data(vld::Node* node_vld){
  //---------------------------

  eng::Node* node_engine = node_vld->get_node_engine();
  dat::Node* node_data = node_engine->get_node_data();
  ldr::Node* node_loader = node_engine->get_node_loader();

  this->node_engine = node_vld->get_node_engine();
  this->vld_struct = node_vld->get_vld_struct();
  this->dat_database = node_data->get_database();
  this->ldr_loader = node_loader->get_loader();
  this->dat_set = new dat::Set();
  this->dat_entity = node_data->get_entity();

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::create_object(){
  if(vld_struct->data.object != nullptr) return;
  //---------------------------

  vld_struct->data.object = new utl::entity::Object(node_engine);
  vld_struct->data.object->name = "capture_1";
  vld_struct->data.object->data.name = "velodyne::capture::data";
  vld_struct->data.object->data.topology.type = utl::topology::POINT;
  vld_struct->data.object->data.nb_data_max = 1000000;
  vld_struct->data.object->pose.model[2][3] = 1;
  dat_entity->init_entity(vld_struct->data.object);

  utl::type::Set* set_scene = dat_database->get_set_scene();
  utl::type::Set* set_capture = dat_set->get_or_create_subset(set_scene, "Data");
  dat_set->insert_entity(set_capture, vld_struct->data.object);

  //---------------------------
}

}
