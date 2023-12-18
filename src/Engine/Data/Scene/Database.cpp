#include "Database.h"


namespace eng::data{

//Constructor / Destructor
Database::Database(eng::data::Node* eng_data){
  //---------------------------

  this->data_set = new eng::structure::Set("Data");

  //---------------------------
}
Database::~Database(){}

//Main function
void Database::init_set(){
  //---------------------------

  data_set->add_new_set("World");
  data_set->add_new_set("Scene");

eng::structure::Set* set = data_set->get_set("Scene");
set->add_new_set("coucou");
  //---------------------------
}

void Database::assign_ID(eng::structure::Entity* entity){
  //----------------------------

  if(entity->ID == -1){
    entity->ID = data_set->ID_entity++;
  }

  //----------------------------
}

}
