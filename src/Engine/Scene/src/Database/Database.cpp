#include "Database.h"

#include <Scene/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Database::Database(eng::scene::Node* node_scene){
  //---------------------------

  this->data_set = new utl::type::Set("Data");

  //---------------------------
}
Database::~Database(){}

//Main function
void Database::init_set(){
  //---------------------------

  set_world = data_set->create_subset("World");
  set_world->is_suppressible = false;

  set_scene = data_set->create_subset("Scene");
  set_scene->is_suppressible = false;

  //---------------------------
}

void Database::assign_UID(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //----------------------------

  if(entity->UID == -1){
    entity->UID = data_set->UID++;
  }

  //----------------------------
}
void Database::assign_UID(utl::type::Data* data){
  if(data == nullptr) return;
  //----------------------------

  if(data->UID == -1){
    data->UID = data_set->UID++;
  }

  //----------------------------
}

}
