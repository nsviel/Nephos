#include "Manager.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>


namespace cam{

//Constructor / Destructor
Manager::Manager(cam::Node* node_camera){
  //---------------------------

  this->node_engine = node_camera->get_node_engine();
  this->dat_set = new dat::Set();

  this->camera_ID = 0;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_camera(){
  //---------------------------

  sce::Node* node_scene = node_engine->get_node_scene();
  dat::Node* node_data = node_engine->get_node_data();

  gly::Node* node_glyph = node_scene->get_node_glyph();
  dat::Database* dat_database = node_data->get_database();
  utl::type::Set* set_main = dat_database->get_set_main();
  utl::type::Set* set_world = dat_set->get_subset(set_main, "World");

  cam::Entity* camera = new cam::Entity();
  camera->name = "camera_" + to_string(camera_ID++);
  camera->is_suppressible = false;
  camera->is_movable = false;
  node_glyph->create_glyph_camera(camera);
  dat_set->insert_entity(set_world, camera);

  this->vec_camera.push_back(camera);
  this->current_camera = camera;

  //---------------------------
}
void Manager::reset(){
  //---------------------------

  for(int i=0; i<vec_camera.size(); i++){
    cam::Entity* camera = vec_camera[i];
    camera->reset_entity();
  }

  //---------------------------
}


}
