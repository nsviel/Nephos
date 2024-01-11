#include "Database.h"


namespace eng::scene{

//Constructor / Destructor
Database::Database(eng::scene::Node* node_scene){
  //---------------------------

  this->data_set = new eng::data::Set("Data");

  //---------------------------
}
Database::~Database(){}

//Main function
void Database::init_set(){
  //---------------------------

  data_set->add_new_set("World");
  data_set->add_new_set("Scene");


//eng::data::Set* set = data_set->get_set("Scene");
//set->add_new_set("coucou");
  //---------------------------
}

void Database::assign_ID(eng::data::Entity* entity){
  if(entity == nullptr) return;
  //----------------------------

  if(entity->ID == -1){
    entity->ID = data_set->ID_entity++;
  }

  //----------------------------
}

}
