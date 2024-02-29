#include "World.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Vulkan/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
World::World(eng::scene::Node* node_scene){
  //---------------------------

  eng::Node* engine = node_scene->get_node_engine();
  vk::Node* node_vulkan = engine->get_node_vulkan();

  this->vk_graphical = node_vulkan->get_vk_graphical();
  this->sce_database = node_scene->get_scene_database();

  //---------------------------
}
World::~World(){}

//World function
void World::init(){
  //---------------------------

  //Get scene set
  utl::type::Set* data_set = sce_database->get_set_main();
  this->set_world = data_set->get_subset("World");

  //---------------------------
}


}
