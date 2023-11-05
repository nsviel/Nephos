#include "Scene.h"
#include "Database.h"
#include "../Data.h"
#include "../Load/Loader.h"

#include <Engine.h>
#include <VK_main/VK_engine.h>
#include <ENG_camera/Camera.h>
#include <ENG_operation/Transformation/Attribut.h>


//ConsScenetor / DesScenetor
Scene::Scene(Data* data){
  //---------------------------

  Engine* engine = data->get_engine();
  this->data = data;
  this->database = data->get_dataManager();
  this->vk_engine = engine->get_vk_engine();
  this->cameraManager = engine->get_cameraManager();
  this->attributManager = new Attribut();

  this->ID_obj = 0;

  //---------------------------
}
Scene::~Scene(){}

//Scene function
void Scene::init_set(){
  list<Set*>* list_data = database->get_list_data_scene();
  //---------------------------

  //Glyph set
  this->set_glyph = new Set("Glyph");
  list_data->push_back(set_glyph);

  //Scene set
  this->set_scene = new Set("Scene");
  list_data->push_back(set_scene);

  //---------------------------
}
void Scene::init_scene(){
  Loader* loaderManager = data->get_loaderManager();
  //---------------------------

  //Load init object
  vector<string> vec_path;
  vec_path.push_back( "../media/point_cloud/dragon.ply");
  vector<Object*> vec_obj = loaderManager->load_objects(vec_path);

  //---------------------------
}
void Scene::reset_scene(){
  //---------------------------

  for(int i=0; i<set_scene->list_obj.size(); i++){
    Object* object = *next(set_scene->list_obj.begin(),i);
    object->reset();
  }

  //---------------------------
}

//Insertion / deletion
void Scene::insert_glyph_object(Object* object){
  //---------------------------

  object->ID = ID_obj++;
  object->is_suppressible = false;
  vk_engine->insert_glyph_in_engine(object);
  set_glyph->list_obj.push_back(object);
  set_glyph->selected_obj = object;
  set_glyph->nb_object++;

  //---------------------------
}
void Scene::insert_scene_object(Object* object){
  //---------------------------

  //Set new object functions
  object->ID = ID_obj++;
  vk_engine->insert_object_in_engine(object);
  attributManager->compute_MinMax(object);

  //Insert it into database
  set_scene->list_obj.push_back(object);
  set_scene->selected_obj = object;
  set_scene->nb_object++;

  //---------------------------
}
void Scene::delete_scene_object(Object* object){
  //---------------------------

  //Delete it from database and engine
  for(int i=0; i<set_scene->list_obj.size(); i++){
    Object* object_list = *next(set_scene->list_obj.begin(),i);
    if(object->ID == object_list->ID){
      set_scene->list_obj.remove(object);
      vk_engine->remove_object_in_engine(object);
      set_scene->nb_object--;
    }
  }

  //---------------------------
}
void Scene::empty_scene_set(){
  //---------------------------

  for(int i=0; i<set_scene->list_obj.size(); i++){
    Object* object = *next(set_scene->list_obj.begin(),i);

    set_scene->list_obj.remove(object);
    vk_engine->remove_object_in_engine(object);
    set_scene->nb_object--;
  }

  //---------------------------
}

//Object
void Scene::selected_object_next(){
  Object* selected = set_scene->selected_obj;
  //----------------------------

  for(int i=0; i<set_scene->list_obj.size(); i++){
    Object* object = *next(set_scene->list_obj.begin(), i);

    if(selected->ID == object->ID){
      Object* selection;

      if((i + 1) < set_scene->list_obj.size()){
        selection = *next(set_scene->list_obj.begin(), i + 1);
      }else{
        selection = *next(set_scene->list_obj.begin(), 0);
      }

      set_scene->selected_obj = selection;
    }
  }

  //----------------------------
}

//Loop function
void Scene::loop(){
  list<Set*>* list_data = database->get_list_data_scene();
  list<Set*>* list_glyph = database->get_list_data_glyph();
  //----------------------------

  this->loop_list(list_data);
  this->loop_list(list_glyph);

  //----------------------------
}
void Scene::loop_list(list<Set*>* list_data){
  //----------------------------

  for(int i=0; i<list_data->size(); i++){
    Set* set = *next(list_data->begin(), i);
    for(int j=0; j<set->list_obj.size(); j++){
      Object* object = *next(set->list_obj.begin(), j);
      cameraManager->compute_cam_mvp(object);
    }
  }

  //----------------------------
}
