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

}
