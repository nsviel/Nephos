#include "Scene.h"
#include "Database.h"
#include <Engine/Data/Namespace.h>

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>
#include <Engine/Camera/Namespace.h>


namespace eng::data{

//ConsScenetor / DesScenetor
Scene::Scene(eng::data::Node* eng_data){
  //---------------------------

  Engine* engine = eng_data->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->eng_data = eng_data;
  this->eng_database = eng_data->get_eng_database();
  this->vk_engine = eng_vulkan->get_vk_engine();
  this->eng_camera = engine->get_eng_camera();
  this->attributManager = new eng::ope::Attribut();

  this->ID_obj = 0;

  //---------------------------
}
Scene::~Scene(){}

//Scene function
void Scene::init(){
  eng::data::Loader* eng_loader = eng_data->get_eng_loader();
  //---------------------------

  //Load init object
  vector<string> vec_path;
  vec_path.push_back( "../media/point_cloud/dragon.ply");
  //vector<eng::structure::Object*> vec_obj = eng_loader->load_objects(vec_path);

  //---------------------------
}
void Scene::loop(){
  list<eng::structure::Set*>* list_set = eng_database->get_list_set();
  //----------------------------

  for(int i=0; i<list_set->size(); i++){
    eng::structure::Set* set = *next(list_set->begin(), i);
    for(int j=0; j<set->list_entity.size(); j++){
      eng::structure::Entity* entity = *next(set->list_entity.begin(), j);

      //Object operation
      if(eng::structure::Object* object = dynamic_cast<eng::structure::Object*>(entity)){
        eng_camera->compute_cam_mvp(object);
     }
    }
  }

  //----------------------------
}
void Scene::reset(){
  list<eng::structure::Set*>* list_set = eng_database->get_list_set();
  //---------------------------

  for(int i=0; i<list_set->size(); i++){
    eng::structure::Set* set = *next(list_set->begin(), i);

    for(int j=0; j<set->list_entity.size(); j++){
      eng::structure::Entity* entity = *next(set->list_entity.begin(), j);
      entity->reset();
    }
  }

  //---------------------------
}

//Insertion / deletion
void Scene::insert_object_glyph(eng::structure::Object* object){
  eng::structure::Set* set_glyph = eng_database->get_set("Glyph");
  //---------------------------

  //Insert into engine
  eng_database->assign_ID(object);
  object->is_suppressible = false;
  vk_engine->insert_object_in_engine(object);

  //Insert it into database
  set_glyph->list_entity.push_back(object);
  set_glyph->selected_entity = object;
  set_glyph->nb_entity++;

  //---------------------------
}
void Scene::insert_object_scene(eng::structure::Object* object){
  eng::structure::Set* set_scene = eng_database->get_set("Scene");
  //---------------------------

  //Insert into engine
  eng_database->assign_ID(object);
  vk_engine->insert_object_in_engine(object);
  attributManager->compute_MinMax(object);

  //Insert it into database
  set_scene->list_entity.push_back(object);
  set_scene->selected_entity = object;
  set_scene->nb_entity++;

  //---------------------------
}
void Scene::update_object(eng::structure::Object* object){
  //---------------------------

  vk_engine->insert_object_in_engine(object);
  attributManager->compute_MinMax(object);

  //---------------------------
}
void Scene::delete_object_scene(eng::structure::Entity* entity){
  eng::structure::Set* set_scene = eng_database->get_set("Scene");
  //---------------------------

  //Selected next entity
  set_scene->select_next_object();

  //Delete it from database and engine
  for(int i=0; i<set_scene->list_entity.size(); i++){
    eng::structure::Object* object_list = (eng::structure::Object*)*next(set_scene->list_entity.begin(),i);
    if(entity->ID == object_list->ID){
      set_scene->list_entity.remove(entity);
      vk_engine->remove_object_in_engine((eng::structure::Object*)entity);
      set_scene->nb_entity--;
    }
  }

  //---------------------------
}
void Scene::delete_object_scene_all(){
  eng::structure::Set* set_scene = eng_database->get_set("Scene");
  //---------------------------

  for(int i=0; i<set_scene->list_entity.size(); i++){
    eng::structure::Object* object = (eng::structure::Object*)*next(set_scene->list_entity.begin(),i);

    set_scene->list_entity.remove(object);
    vk_engine->remove_object_in_engine(object);
    set_scene->nb_entity--;
  }

  //---------------------------
}

}
