#include "Data.h"

#include <Velodyne/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Data::Data(vld::Node* node_vld){
  //---------------------------

  sce::Node* node_scene = node_vld->get_node_scene();

  this->node_engine = node_vld->get_node_engine();
  this->vld_struct = node_vld->get_vld_struct();
  this->sce_database = node_scene->get_scene_database();
  this->ldr_loader = node_scene->get_scene_loader();
  this->sce_set = new dat::Set();
  this->sce_entity = node_scene->get_scene_entity();

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
  sce_entity->init_entity(vld_struct->data.object);

  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::type::Set* set_capture = sce_set->get_or_create_subset(set_scene, "Data");
  sce_set->insert_entity(set_capture, vld_struct->data.object);

  //---------------------------
}

}
