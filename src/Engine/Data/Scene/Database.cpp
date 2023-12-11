#include "Database.h"


namespace eng::data{

//Constructor / Destructor
Database::Database(eng::data::Node* eng_data){
  //---------------------------

  this->ID_obj = 0;

  this->list_data = new list<eng::structure::Set*>();
  this->list_glyph = new list<eng::structure::Set*>();

  //---------------------------
}
Database::~Database(){}

}
