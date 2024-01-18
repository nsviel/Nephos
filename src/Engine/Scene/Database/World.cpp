#include "World.h"


namespace eng::scene{

//Constructor / Destructor
World::World(eng::scene::Node* node_scene){
  //---------------------------

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


}
