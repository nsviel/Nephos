#include "Manager.h"

#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>


namespace cam{

//Constructor / Destructor
Manager::Manager(cam::Node* node_camera){
  //---------------------------

  dat::Node* node_data = node_camera->get_node_data();

  this->dat_glyph = node_data->get_glyph();
  this->dat_graph = node_data->get_database();
  this->dat_set = new dat::Set();

  this->camera_ID = 0;

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_camera(){
  //---------------------------
  dat::base::Set* set_main = dat_graph->get_set_main();
  dat::base::Set* set_world = dat_set->get_subset(set_main, "Scene");

  cam::Entity* camera = new cam::Entity();
  camera->name = "camera_" + to_string(camera_ID++);
  camera->is_suppressible = false;
  camera->is_movable = false;
  dat_glyph->create_glyph_camera(camera);
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
