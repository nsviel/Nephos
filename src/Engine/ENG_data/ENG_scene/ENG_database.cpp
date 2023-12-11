#include "ENG_database.h"

#include "../ENG_data.h"


//Constructor / Destructor
ENG_database::ENG_database(ENG_data* eng_data){
  //---------------------------

  this->ID_obj = 0;

  this->list_data = new list<eng::structure::Set*>();
  this->list_glyph = new list<eng::structure::Set*>();

  //---------------------------
}
ENG_database::~ENG_database(){}
