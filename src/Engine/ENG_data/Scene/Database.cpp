#include "Database.h"

#include "../ENG_data.h"


//Constructor / Destructor
Database::Database(ENG_data* eng_data){
  //---------------------------

  this->ID_obj = 0;

  this->list_data = new list<Set*>();
  this->list_glyph = new list<Set*>();

  //---------------------------
}
Database::~Database(){}
