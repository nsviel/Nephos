#include "Manager.h"

#include <Engine/Engine.h>


namespace eng::camera{

//Constructor / Destructor
Manager::Manager(Engine* engine){
  //---------------------------

  this->engine = engine;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_camera(){
  //---------------------------

  eng::scene::Node* node_scene = engine->get_node_scene();
  eng::scene::Glyph* sce_glyph = node_scene->get_scene_glyph();
  eng::scene::Database* sce_database = node_scene->get_scene_database();
  eng::data::Set* data_set = sce_database->get_data_set();
  eng::data::Set* set_camera = data_set->get_set("Camera");

  eng::data::Camera* camera = new eng::data::Camera();
  sce_glyph->create_glyph_camera(camera);
  set_camera->insert_entity(camera);

  this->vec_camera.push_back(camera);
  this->current_camera = camera;

  //---------------------------
}
void Manager::reset(){
  //---------------------------

  for(int i=0; i<vec_camera.size(); i++){
    eng::data::Camera* camera = vec_camera[i];
    camera->reset();
  }

  //---------------------------
}


}
