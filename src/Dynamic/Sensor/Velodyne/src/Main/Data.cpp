#include "Data.h"

#include <Velodyne/Namespace.h>
#include <Data/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Data::Data(vld::Node* node_velodyne){
  //---------------------------

  dat::Node* node_data = node_velodyne->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->vld_struct = node_velodyne->get_vld_struct();
  this->dat_graph = node_graph->get_gph_graph();
  this->dat_set = node_element->get_dat_set();
  this->dat_entity = node_element->get_dat_entity();

  //---------------------------
}
Data::~Data(){}

//Main function
void Data::create_object(){
  if(vld_struct->data.object != nullptr) return;
  //---------------------------
/*
  vld_struct->data.object = new dat::base::Object();
  vld_struct->data.object->name = "capture_1";
  vld_struct->data.object->data->name = "velodyne::capture::data";
  vld_struct->data.object->data->topology.type = utl::topology::POINT;
  vld_struct->data.object->data->size_max = 1000000;
  vld_struct->data.object->pose.model[2][3] = 1;
  dat_entity->init_entity(vld_struct->data.object);

  std::shared_ptr<dat::base::Set> set_scene = dat_graph->get_set_graph();
  std::shared_ptr<dat::base::Set> set_capture = dat_set->get_or_create_subset(set_scene, "Data");
  dat_set->insert_entity(set_capture, vld_struct->data.object);
*/
  //---------------------------
}

}
