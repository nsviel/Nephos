#include "Database.h"


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

  data_set->add_new_set("World");
  data_set->add_new_set("Scene");

  //---------------------------
}

void Database::assign_ID(utl::type::Entity* entity){
  if(entity == nullptr) return;
  //----------------------------

  if(entity->UID == -1){
    entity->UID = data_set->UID++;
  }

  //----------------------------
}
void Database::assign_ID(utl::type::Data* data){
  if(data == nullptr) return;
  //----------------------------

  if(data->UID == -1){
    data->UID = data_set->UID++;
  }

  //----------------------------
}

}
