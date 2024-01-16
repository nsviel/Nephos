#include "Scene.h"

#include <Utility/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>


namespace eng::scene{

//ConsScenetor / DesScenetor
Scene::Scene(eng::scene::Node* node_scene){
  //---------------------------

  Engine* engine = node_scene->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->sce_database = node_scene->get_scene_database();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->vk_engine = eng_vulkan->get_vk_engine();
  this->ope_attribut = new eng::ope::Attribut();
  this->sce_loader = node_scene->get_scene_loader();

  this->ID_obj = 0;

  //---------------------------
}
Scene::~Scene(){}

//Scene function
void Scene::init(){
  //---------------------------

  //Initial scene entities
  //vector<string> vec_path;
  //vec_path.push_back( "../media/point_cloud/dragon.ply");
  //vector<entity::Object*> vec_obj = eng_loader->load_entitys(vec_path);

  //---------------------------
}
void Scene::loop(){
  utl::base::Set* data_set = sce_database->get_data_set();
  //----------------------------

  for(int i=0; i<data_set->list_set.size(); i++){
    utl::base::Set* set = *next(data_set->list_set.begin(), i);
    for(int j=0; j<set->list_entity.size(); j++){
      entity::Entity* entity = *next(set->list_entity.begin(), j);
      entity->update_entity();
    }
  }

  //----------------------------
}
void Scene::reset(){
  utl::base::Set* data_set = sce_database->get_data_set();
  //---------------------------

  data_set->reset();

  //---------------------------
}
entity::Entity* Scene::get_selected_entity(){
  utl::base::Set* data_set = sce_database->get_data_set();
  //---------------------------

  utl::base::Set* set_scene = data_set->get_set("Scene");
  entity::Entity* entity = set_scene->selected_entity;

  //---------------------------
  return entity;
}

//Entity
entity::Entity* Scene::import_entity(std::string path){
  //---------------------------

  entity::Entity* entity = sce_loader->load_entity(path);
  this->insert_entity_scene(entity);
  sce_database->assign_ID(entity);

  //---------------------------
  return entity;
}
void Scene::insert_entity_scene(entity::Entity* entity){
  utl::base::Set* data_set = sce_database->get_data_set();
  utl::base::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  set_scene->insert_entity(entity);

  //---------------------------
}
void Scene::delete_entity(entity::Entity* entity){
  utl::base::Set* data_set = sce_database->get_data_set();
  utl::base::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  //Selected next entity
  set_scene->select_next_entity();

  //Delete it from database and engine
  for(int i=0; i<set_scene->list_entity.size(); i++){
    entity::Entity* entity_scene = *next(set_scene->list_entity.begin(),i);

    //Check if entity is present in the scene
    if(entity->UID == entity_scene->UID){
      set_scene->remove_entity(entity);
      entity->remove_entity();
    }
  }

  //---------------------------
}
void Scene::delete_entity_all(){
  utl::base::Set* data_set = sce_database->get_data_set();
  utl::base::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  for(int i=0; i<set_scene->list_entity.size(); i++){
    entity::Entity* entity = *next(set_scene->list_entity.begin(),i);

    set_scene->remove_entity(entity);
    entity->remove_entity();
  }

  //---------------------------
}

//Object
void Scene::insert_object_scene(entity::Object* object){
  utl::base::Set* data_set = sce_database->get_data_set();
  utl::base::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  this->insert_object(object);
  set_scene->insert_entity(object);

  //---------------------------
}
void Scene::insert_object(entity::Object* object){
  //---------------------------

  sce_database->assign_ID(object);
  vk_engine->insert_data_in_engine(object->data);
  sce_glyph->create_glyph_object(object);

  //---------------------------
}
void Scene::update_object(entity::Object* object){
  //---------------------------

  vk_engine->insert_data_in_engine(object->data);
  ope_attribut->compute_MinMax(object->data);

  //---------------------------
}
void Scene::remove_object(entity::Object* object){
  //---------------------------

  sce_glyph->remove_glyph_object(object);
  vk_engine->remove_data_in_engine(object->data);

  //---------------------------
}



}
