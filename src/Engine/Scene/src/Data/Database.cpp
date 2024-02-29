#include "Database.h"

#include <Scene/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Database::Database(eng::scene::Node* node_scene){
  //---------------------------

  this->set_main = new utl::type::Set("Data");

  //---------------------------
}
Database::~Database(){}

//Main function
void Database::init(){
  //---------------------------

  set_world = set_main->create_subset("World");
  set_world->is_suppressible = false;

  set_scene = set_main->create_subset("Scene");
  set_scene->is_suppressible = false;

  //---------------------------
}
void Database::loop(){
  //----------------------------

  set_main->update();

  //----------------------------
}
void Database::reset(){
  //---------------------------

  set_main->reset();

  //---------------------------
}

//Subfunction
void Database::assign_UID(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //----------------------------

  if(entity->UID == -1){
    entity->UID = set_main->UID++;
  }

  //----------------------------
}
void Database::assign_UID(utl::type::Data* data){
  if(data == nullptr) return;
  //----------------------------

  if(data->UID == -1){
    data->UID = set_main->UID++;
  }

  //----------------------------
}

}
