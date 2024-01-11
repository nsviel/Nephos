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

  eng::data::Camera* camera = new eng::data::Camera();
  sce_glyph->create_glyph_camera(camera);

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
