#include "World.h"

#include <Engine/Node.h>
#include <Engine/Scene/Namespace.h>
#include <Vulkan/Node.h>
#include <Vulkan/VK_main/Engine.h>


namespace eng::scene{

//Constructor / Destructor
World::World(eng::scene::Node* sce_node){
  //---------------------------

  eng::Node* engine = sce_node->get_engine();
  vk::Node* eng_vulkan = engine->get_eng_vulkan();

  this->vk_engine = eng_vulkan->get_vk_engine();
  this->sce_database = sce_node->get_scene_database();

  //---------------------------
}
World::~World(){}

//World function
void World::init(){
  //---------------------------

  //Get scene set
  utl::type::Set* data_set = sce_database->get_data_set();
  this->set_world = data_set->get_set("World");

  //---------------------------
}

//Entity function
void World::import_entity(utl::type::Entity* entity){
  //---------------------------

  set_world->insert_entity(entity);
  this->init_entity(entity);

  //---------------------------
}
void World::init_entity(utl::type::Entity* entity){
  //---------------------------

  //Init entity
  sce_database->assign_UID(entity);
  vk_engine->insert_data_in_engine(entity->get_data(), entity->get_pose());

  //Init entity data
  utl::type::Data* data = entity->get_data();
  sce_database->assign_UID(data);
  vk_engine->insert_data_in_engine(entity->get_data(), entity->get_pose());

  //Init entity data vector
  vector<utl::type::Data*> vec_data = entity->get_vec_data();
  for(int j=0; j<vec_data.size(); j++){
    sce_database->assign_UID(vec_data[j]);
    vk_engine->insert_data_in_engine(vec_data[j], entity->get_pose());
  }

  //---------------------------
}
void World::update_entity(utl::type::Entity* entity){
  //---------------------------

  //Update entity data
  vk_engine->insert_data_in_engine(entity->get_data(), entity->get_pose());

  //Update entity data vector
  vector<utl::type::Data*> vec_data = entity->get_vec_data();
  for(int j=0; j<vec_data.size(); j++){
    vk_engine->insert_data_in_engine(vec_data[j], entity->get_pose());
    //cam_control->compute_camera_mvp(vec_data[j]);
  }

  //---------------------------
}

}
