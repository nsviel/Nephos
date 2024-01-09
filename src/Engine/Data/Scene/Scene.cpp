#include "Scene.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Camera/Namespace.h>


namespace eng::scene{

//ConsScenetor / DesScenetor
Scene::Scene(eng::scene::Node* sce_node){
  //---------------------------

  Engine* engine = sce_node->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->sce_node = sce_node;
  this->sce_database = sce_node->get_scene_database();
  this->sce_glyph = sce_node->get_scene_glyph();
  this->vk_engine = eng_vulkan->get_vk_engine();
  this->eng_camera = engine->get_eng_camera();
  this->sce_operation = new eng::scene::Operation(sce_node);
  this->attributManager = new eng::ope::Attribut();

  this->ID_obj = 0;

  //---------------------------
}
Scene::~Scene(){}

//Scene function
void Scene::init(){
  eng::scene::Loader* eng_loader = sce_node->get_scene_loader();
  //---------------------------

  //Initial scene entities
  //vector<string> vec_path;
  //vec_path.push_back( "../media/point_cloud/dragon.ply");
  //vector<eng::data::Object*> vec_obj = eng_loader->load_objects(vec_path);

  //---------------------------
}
void Scene::loop(){
  eng::data::Set* data_set = sce_database->get_data_set();
  //----------------------------

  for(int i=0; i<data_set->list_set.size(); i++){
    eng::data::Set* set = *next(data_set->list_set.begin(), i);
    for(int j=0; j<set->list_entity.size(); j++){
      eng::data::Entity* entity = *next(set->list_entity.begin(), j);
      sce_operation->update_entity(entity);
    }
  }

  //----------------------------
}
void Scene::reset(){
  eng::data::Set* data_set = sce_database->get_data_set();
  //---------------------------

  data_set->reset();

  //---------------------------
}
eng::data::Entity* Scene::get_selected_entity(){
  eng::data::Set* data_set = sce_database->get_data_set();
  //---------------------------

  eng::data::Set* set_scene = data_set->get_set("Scene");
  eng::data::Entity* entity = set_scene->selected_entity;

  //---------------------------
  return entity;
}

//Entity
void Scene::insert_entity_scene(eng::data::Entity* entity){
  eng::data::Set* data_set = sce_database->get_data_set();
  eng::data::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  set_scene->insert_entity(entity);

  //---------------------------
}
void Scene::delete_entity(eng::data::Entity* entity){
  eng::data::Set* data_set = sce_database->get_data_set();
  eng::data::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  //Selected next entity
  set_scene->select_next_entity();

  //Delete it from database and engine
  for(int i=0; i<set_scene->list_entity.size(); i++){
    eng::data::Entity* entity_scene = *next(set_scene->list_entity.begin(),i);

    if(entity->ID == entity_scene->ID){
      set_scene->list_entity.remove(entity);
      set_scene->nb_entity--;

      //If entity is an object
      if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){say("object");
        this->remove_object(object);
      }

      //If entity is a k4a device
    }
  }

  //---------------------------
}
void Scene::delete_entity_all(){
  eng::data::Set* data_set = sce_database->get_data_set();
  eng::data::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  for(int i=0; i<set_scene->list_entity.size(); i++){
    eng::data::Object* object = (eng::data::Object*)*next(set_scene->list_entity.begin(),i);

    set_scene->list_entity.remove(object);
    vk_engine->remove_object_in_engine(object);
    set_scene->nb_entity--;
  }

  //---------------------------
}

//Object
void Scene::insert_object_scene(eng::data::Object* object){
  eng::data::Set* data_set = sce_database->get_data_set();
  eng::data::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  this->insert_object(object);
  set_scene->insert_entity(object);

  //---------------------------
}
void Scene::insert_object(eng::data::Object* object){
  //---------------------------

  sce_database->assign_ID(object);
  vk_engine->insert_object_in_engine(object);
  sce_glyph->create_glyph_object(object);

  //---------------------------
}
void Scene::update_object(eng::data::Object* object){
  //---------------------------

  vk_engine->insert_object_in_engine(object);
  attributManager->compute_MinMax(object);

  //---------------------------
}
void Scene::remove_object(eng::data::Object* object){
  //---------------------------

  sce_glyph->remove_glyph_object(object);
  vk_engine->remove_object_in_engine(object);

  //---------------------------
}



}
