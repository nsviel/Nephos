#include "Scene.h"

#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>


namespace eng::scene{

//Constructor / Destructor
Scene::Scene(eng::scene::Node* node_scene){
  //---------------------------

  Engine* engine = node_scene->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->sce_database = node_scene->get_scene_database();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->vk_engine = eng_vulkan->get_vk_engine();
  this->ope_attribut = new eng::ope::Attribut();
  this->sce_loader = node_scene->get_scene_loader();

  //---------------------------
}
Scene::~Scene(){}

//Main function
void Scene::init(){
  //---------------------------

  //Initial scene entities
  //vector<string> vec_path;
  //vec_path.push_back( "../media/point_cloud/dragon.ply");
  //vector<entity::Object*> vec_obj = eng_loader->load_entitys(vec_path);

  //Get scene set
  utl::type::Set* data_set = sce_database->get_data_set();
  this->set_scene = data_set->get_set("Scene");

  //---------------------------
}
void Scene::loop(){
  utl::type::Set* data_set = sce_database->get_data_set();
  //----------------------------

  data_set->update();

  //----------------------------
}
void Scene::reset(){
  utl::type::Set* data_set = sce_database->get_data_set();
  //---------------------------

  data_set->reset();

  //---------------------------
}

//Entity
utl::type::Entity* Scene::import_entity(std::string path){
  //---------------------------

  //Entity importation stuff
  utl::type::Entity* entity = sce_loader->load_entity(path);
  set_scene->insert_entity(entity);
  this->init_entity(entity);

  //---------------------------
  return entity;
}
void Scene::import_entity(utl::type::Entity* entity){
  //---------------------------

  //Entity importation stuff
  set_scene->insert_entity(entity);
  this->init_entity(entity);

  //---------------------------
}
void Scene::init_entity(utl::type::Entity* entity){
  //---------------------------

  //Init entity
  sce_database->assign_UID(entity);
  vk_engine->insert_data_in_engine(entity->get_data());

  //If object; create dedicated glyphs
  if(entity::Object* object = dynamic_cast<entity::Object*>(entity)){
    sce_glyph->create_glyph_object(object);
  }

  //Init entity data
  utl::type::Data* data = entity->get_data();
  sce_database->assign_UID(data);
  vk_engine->insert_data_in_engine(data);

  //Init entity vector data
  vector<utl::type::Data*> vec_data = entity->get_vec_data();
  for(int j=0; j<vec_data.size(); j++){
    sce_database->assign_UID(vec_data[j]);
    vk_engine->insert_data_in_engine(vec_data[j]);
  }

  //---------------------------
}
void Scene::delete_entity(utl::type::Entity* entity){
  //---------------------------

  //Selected next entity
  set_scene->select_next_entity();

  //Delete it from database and engine
  set_scene->delete_entity(entity);

  //---------------------------
}
void Scene::assign_entity_UID(utl::type::Entity* entity){
  //---------------------------

  sce_database->assign_UID(entity);

  //---------------------------
}


}
