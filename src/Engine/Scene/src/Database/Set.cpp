#include "Set.h"

#include <Engine/Namespace.h>
#include <Operation/Namespace.h>
#include <Scene/Namespace.h>
#include <Vulkan/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Set::Set(eng::scene::Node* node_scene){
  //---------------------------

  eng::Node* engine = node_scene->get_node_engine();
  vk::Node* node_vulkan = engine->get_node_vulkan();

  this->sce_database = node_scene->get_scene_database();
  this->sce_glyph = node_scene->get_scene_glyph();
  this->vk_graphical = node_vulkan->get_vk_graphical();

  //---------------------------
}
Set::~Set(){}

//Main function
void Set::init(){
  //---------------------------

  //Get scene set
  utl::type::Set* data_set = sce_database->get_set_main();
  this->set_scene = data_set->get_subset("Set");

  //---------------------------
}
void Set::loop(){
  utl::type::Set* data_set = sce_database->get_set_main();
  //----------------------------

  data_set->update();

  //----------------------------
}
void Set::reset(){
  utl::type::Set* data_set = sce_database->get_set_main();
  //---------------------------

  data_set->reset();

  //---------------------------
}

//Entity function
void Set::import_entity(utl::type::Entity* entity){
  //---------------------------

  //Entity importation stuff
  set_scene->insert_entity(entity);
  this->init_entity(entity);

  //---------------------------
}
void Set::init_entity(utl::type::Entity* entity){
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
void Set::assign_entity_UID(utl::type::Entity* entity){
  //---------------------------

  sce_database->assign_UID(entity);

  //---------------------------
}

//Set function
void Set::delete_subset(utl::type::Set* set){
  if(set->is_suppressible == false) return;
  //---------------------------

  //Selected next entity
  //set_scene->select_next_entity();

  //Delete it from database and engine
  //set_scene->delete_scene_entity(entity);

  //---------------------------
}
utl::type::Set* Set::get_or_create_subset(string name){
  //---------------------------



  //---------------------------
}


}
