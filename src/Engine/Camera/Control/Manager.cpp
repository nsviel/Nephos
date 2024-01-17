#include "Manager.h"

#include <Engine/Engine.h>
#include <Utility/Base/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Manager::Manager(Engine* engine){
  //---------------------------

  this->engine = engine;

  this->camera_ID = 0;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_camera(){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  eng::scene::Database* sce_database = node_scene->get_scene_database();
  utl::type::Set* data_set = sce_database->get_data_set();
  utl::type::Set* set_world = data_set->get_set("World");

  entity::Camera* camera = new entity::Camera();
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
    entity::Camera* camera = vec_camera[i];
    camera->reset_entity();
  }

  //---------------------------
}


}
