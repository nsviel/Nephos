#include "Scene.h"

#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Scene/Namespace.h>
#include <Vulkan/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Scene::Scene(eng::scene::Node* node_scene){
  //---------------------------

  eng::Node* engine = node_scene->get_node_engine();
  vk::Node* node_vulkan = engine->get_node_vulkan();

  this->sce_database = node_scene->get_scene_database();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->vk_graphical = node_vulkan->get_vk_graphical();

  //---------------------------
}
Scene::~Scene(){}

//Main function
void Scene::init(){
  //---------------------------

  //Get scene set
  utl::type::Set* data_set = sce_database->get_set_main();
  this->set_scene = data_set->get_subset("Scene");

  //---------------------------
}
void Scene::loop(){
  utl::type::Set* data_set = sce_database->get_set_main();
  //----------------------------

  data_set->update();

  //----------------------------
}
void Scene::reset(){
  utl::type::Set* data_set = sce_database->get_set_main();
  //---------------------------

  data_set->reset();

  //---------------------------
}

//Entity function
void Scene::assign_entity_UID(utl::type::Entity* entity){
  //---------------------------

  sce_database->assign_UID(entity);

  //---------------------------
}

//Set function
void Scene::delete_subset(utl::type::Set* set){
  if(set->is_suppressible == false) return;
  //---------------------------

  //Selected next entity
  //set_scene->select_next_entity();

  //Delete it from database and engine
  //set_scene->delete_scene_entity(entity);

  //---------------------------
}
utl::type::Set* Scene::get_or_create_subset(string name){
  //---------------------------



  //---------------------------
}


}
