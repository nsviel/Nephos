#include "Manager.h"

#include <Velodyne/Namespace.h>
#include <Scene/Namespace.h>


namespace vld::main{

//Constructor / Destructor
Manager::Manager(vld::Node* node_vld){
  //---------------------------

  eng::scene::Node* node_scene = node_vld->get_node_scene();

  this->vld_struct = node_vld->get_vld_struct();
  this->sce_database = node_scene->get_scene_database();
  this->sce_loader = node_scene->get_scene_loader();
  this->sce_set = new eng::scene::Set();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::init(){
  //---------------------------

  utl::type::Set* set_scene = sce_database->get_set_scene();
  utl::type::Set* set_capture = sce_set->get_or_create_subset(set_scene, "Capture");

  for(int i=0; i<vld_struct->data.num_object; i++){
    utl::entity::Object* object = new utl::entity::Object();

    sce_set->insert_entity(set_capture, object);
    vld_struct->data.vec_object.push_back(object);
  }

  //---------------------------
}

}
