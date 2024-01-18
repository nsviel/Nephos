#include "World.h"

#include <Engine/Engine.h>
#include <Vulkan/Vulkan.h>
#include <Vulkan/VK_main/VK_engine.h>


namespace eng::scene{

//Constructor / Destructor
World::World(eng::scene::Node* node_scene){
  //---------------------------

  Engine* engine = node_scene->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();

  this->vk_engine = eng_vulkan->get_vk_engine();
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
  sce_database->assign_UID(entity);
  vk_engine->insert_data_in_engine(entity->get_data());

  //---------------------------
}

}
