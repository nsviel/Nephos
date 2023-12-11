#include "ENG_database.h"


//Constructor / Destructor
Nodebase::Nodebase(eng::data::Node* eng_data){
  //---------------------------

  this->ID_obj = 0;

  this->list_data = new list<eng::structure::Set*>();
  this->list_glyph = new list<eng::structure::Set*>();

  //---------------------------
}
Nodebase::~Nodebase(){}
