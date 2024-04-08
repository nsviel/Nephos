#include "Capture.h"

#include <Velodyne/Namespace.h>
#include <Scene/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Capture::Capture(vld::Node* node_vld){
  //---------------------------

  eng::scene::Node* node_scene = node_vld->get_node_scene();

  this->node_engine = node_vld->get_node_engine();
  this->vld_struct = node_vld->get_vld_struct();
  this->vld_server = new vld::thread::Server(node_vld);
  this->sce_database = node_scene->get_scene_database();
  this->sce_loader = node_scene->get_scene_loader();
  this->sce_set = new eng::scene::Set();
  this->sce_entity = node_scene->get_scene_entity();

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::init(){
  //---------------------------

  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::type::Set* set_capture = sce_set->get_or_create_subset(set_scene, "Capture");

  for(int i=0; i<vld_struct->data.num_object; i++){
    utl::entity::Object* object = new utl::entity::Object(node_engine);
    object->name = "capture_1";
    object->data.name = "velodyne::capture::data";
    object->data.topology.type = utl::topology::POINT;
    object->data.nb_data_max = 100000;
    object->pose.model[2][3] = 1;
    sce_entity->init_entity(object);

    sce_set->insert_entity(set_capture, object);
    vld_struct->data.vec_object.push_back(object);
  }

  vld_server->start_thread();

  //---------------------------
}
void Capture::clean(){
  //---------------------------

  vld_server->stop_thread();

  //---------------------------
}

}
