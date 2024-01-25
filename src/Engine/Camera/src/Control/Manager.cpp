#include "Manager.h"

#include <Engine/Engine.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Data/Namespace.h>


namespace eng::cam{

//Constructor / Destructor
Manager::Manager(eng::cam::Node* node_camera){
  //---------------------------

  this->engine = node_camera->get_engine();

  this->camera_ID = 0;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_camera(){
  //---------------------------

  eng::scene::Node* sce_node = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = sce_node->get_scene_glyph();
  eng::scene::Database* sce_database = sce_node->get_scene_database();
  utl::type::Set* data_set = sce_database->get_data_set();
  utl::type::Set* set_world = data_set->get_set("World");

  utl::entity::Camera* camera = new utl::entity::Camera();
  camera->name = "camera_" + to_string(camera_ID++);
  camera->is_suppressible = false;
  camera->is_movable = false;
  sce_glyph->create_glyph_camera(camera);
  set_world->insert_entity(camera);

  this->vec_camera.push_back(camera);
  this->current_camera = camera;

  //---------------------------
}
void Manager::reset(){
  //---------------------------

  for(int i=0; i<vec_camera.size(); i++){
    utl::entity::Camera* camera = vec_camera[i];
    camera->reset_entity();
  }

  //---------------------------
}


}
