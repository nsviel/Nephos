#include "Scene.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Camera/Namespace.h>


namespace eng::scene{

//ConsScenetor / DesScenetor
Scene::Scene(eng::scene::Node* eng_data){
  //---------------------------

  Engine* engine = eng_data->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->eng_data = eng_data;
  this->eng_database = eng_data->get_eng_database();
  this->eng_glyph = eng_data->get_eng_glyph();
  this->vk_engine = eng_vulkan->get_vk_engine();
  this->eng_camera = engine->get_eng_camera();
  this->attributManager = new eng::ope::Attribut();

  this->ID_obj = 0;

  //---------------------------
}
Scene::~Scene(){}

//Scene function
void Scene::init(){
  eng::scene::Loader* eng_loader = eng_data->get_eng_loader();
  //---------------------------

  //Load init object
  vector<string> vec_path;
  vec_path.push_back( "../media/point_cloud/dragon.ply");
  //vector<eng::data::Object*> vec_obj = eng_loader->load_objects(vec_path);

  //---------------------------
}
void Scene::loop(){
  eng::data::Set* data_set = eng_database->get_data_set();
  //----------------------------

  for(int i=0; i<data_set->list_set.size(); i++){
    eng::data::Set* set = *next(data_set->list_set.begin(), i);
    for(int j=0; j<set->list_entity.size(); j++){
      eng::data::Entity* entity = *next(set->list_entity.begin(), j);

      if(eng::data::Object* object = dynamic_cast<eng::data::Object*>(entity)){
        eng_camera->compute_cam_mvp(object);
        eng_glyph->update_glyph_object(object);
      }
    }
  }

  //----------------------------
}
void Scene::reset(){
  eng::data::Set* data_set = eng_database->get_data_set();
  //---------------------------

  data_set->reset();

  //---------------------------
}

//Object
void Scene::insert_object_scene(eng::data::Object* object){
  eng::data::Set* data_set = eng_database->get_data_set();
  eng::data::Set* set_scene = data_set->get_set("Scene");
  //---------------------------

  //Insert into engine
  eng_database->assign_ID(object);
  vk_engine->insert_object_in_engine(object);
  attributManager->compute_MinMax(object);
  set_scene->insert_entity(object);
  eng_glyph->create_glyph_object(object);

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

  eng_glyph->remove_glyph_object(object);
  vk_engine->remove_object_in_engine(object);

  //---------------------------
}

//Entity
void Scene::delete_entity(eng::data::Entity* entity){
  eng::data::Set* data_set = eng_database->get_data_set();
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
  eng::data::Set* data_set = eng_database->get_data_set();
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

}
