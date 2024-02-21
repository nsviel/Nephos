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
  this->ope_attribut = new ope::Attribut();

  //---------------------------
}
Scene::~Scene(){}

//Main function
void Scene::init(){
  //---------------------------

  //Initial scene entities
  //vector<string> vec_path;
  //vec_path.push_back( "../media/point_cloud/dragon.ply");
  //vector<utl::entity::Object*> vec_obj = eng_loader->load_entitys(vec_path);

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

//Entity function
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
  vk_graphical->insert_data_in_engine(entity->get_data(), entity->get_pose());

  //If object; create dedicated glyphs
  if(utl::entity::Object* object = dynamic_cast<utl::entity::Object*>(entity)){
    sce_glyph->create_glyph_object(object);
  }

  //Init entity data
  utl::type::Data* data = entity->get_data();
  utl::type::Pose* pose = entity->get_pose();
  sce_database->assign_UID(data);
  vk_graphical->insert_data_in_engine(data, pose);

  //Init entity vector data
  vector<utl::type::Data*> vec_data = entity->get_vec_data();
  for(int j=0; j<vec_data.size(); j++){
    sce_database->assign_UID(vec_data[j]);
    vk_graphical->insert_data_in_engine(vec_data[j], entity->get_pose());
  }

  //---------------------------
}
void Scene::delete_scene_entity(utl::type::Entity* entity){
  if(entity->is_suppressible == false) return;
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

//Set function
void Scene::delete_set(utl::type::Set* set){
  if(set->is_suppressible == false) return;
  //---------------------------

  //Selected next entity
  //set_scene->select_next_entity();

  //Delete it from database and engine
  //set_scene->delete_scene_entity(entity);

  //---------------------------
}


}
