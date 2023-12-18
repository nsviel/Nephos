#include "Database.h"


namespace eng::data{

//Constructor / Destructor
Database::Database(eng::data::Node* eng_data){
  //---------------------------

  this->ID_obj = 0;

  this->list_set = new list<eng::structure::Set*>();

  //---------------------------
}
Database::~Database(){}

void Database::add_new_set(eng::structure::Set* set){
  //---------------------------

  list_set.push_back(set);

  //---------------------------
}

}
