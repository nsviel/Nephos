#include "Manager.h"

#include <Camera/Namespace.h>
#include <Scene/Namespace.h>
#include <Scene/Namespace.h>
#include <Glyph/Namespace.h>


namespace cam{

//Constructor / Destructor
Manager::Manager(cam::Node* node_camera){
  //---------------------------

  this->node_scene = node_camera->get_node_scene();
  this->sce_set = new dat::Set();

  this->camera_ID = 0;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_camera(){
  //---------------------------

  gly::Node* node_glyph = node_scene->get_scene_glyph();
  dat::Database* sce_database = node_scene->get_scene_database();
  utl::type::Set* set_main = sce_database->get_set_main();
  utl::type::Set* set_world = sce_set->get_subset(set_main, "World");

  cam::Entity* camera = new cam::Entity();
  camera->name = "camera_" + to_string(camera_ID++);
  camera->is_suppressible = false;
  camera->is_movable = false;
  node_glyph->create_glyph_camera(camera);
  sce_set->insert_entity(set_world, camera);

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
