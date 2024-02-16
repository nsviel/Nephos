#include "World.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Vulkan/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
World::World(eng::scene::Node* node_scene){
  //---------------------------

  eng::Node* engine = node_scene->get_node_engine();
  vk::Node* eng_vulkan = engine->get_eng_vulkan();

  this->vk_graphical = eng_vulkan->get_vk_graphical();
  this->sce_database = node_scene->get_scene_database();

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
  vk_graphical->insert_data_in_engine(entity->get_data(), entity->get_pose());

  //Init entity data
  utl::type::Data* data = entity->get_data();
  sce_database->assign_UID(data);
  vk_graphical->insert_data_in_engine(entity->get_data(), entity->get_pose());

  //Init entity data vector
  vector<utl::type::Data*> vec_data = entity->get_vec_data();
  for(int j=0; j<vec_data.size(); j++){
    sce_database->assign_UID(vec_data[j]);
    vk_graphical->insert_data_in_engine(vec_data[j], entity->get_pose());
  }

  //---------------------------
}

}
