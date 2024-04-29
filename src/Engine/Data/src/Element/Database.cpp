#include "Database.h"

#include <Data/Namespace.h>


namespace dat{

//Constructor / Destructor
Database::Database(dat::Node* node_data){
  //---------------------------

  this->set_main = new utl::type::Set();
  this->dat_set = new dat::Set();

  //---------------------------
}
Database::~Database(){}

//Main function
void Database::init(){
  //---------------------------

  set_world = dat_set->create_subset(set_main, "World");
  set_world->is_suppressible = false;

  set_scene = dat_set->create_subset(set_main, "Scene");
  set_scene->is_suppressible = false;

  //---------------------------
}
void Database::loop(){
  //----------------------------

  dat_set->update_set(set_main);

  //----------------------------
}
void Database::reset(){
  //---------------------------

  dat_set->reset_set(set_main);

  //---------------------------
}
void Database::clean(){
  //---------------------------

  dat_set->remove_entity_all(set_main);

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
  if(data == nullptr){
    cout<<"[error] data is nullptr"<<endl;
    return;
  }
  //----------------------------

  if(data->UID == -1){
    data->UID = set_main->UID++;
  }

  //----------------------------
}

}
