#include "Database.h"


namespace eng::data{

//Constructor / Destructor
Database::Database(eng::data::Node* eng_data){
  //---------------------------

  this->ID_entity = 0;

  //---------------------------
}
Database::~Database(){}

//Main function
void Database::init_set(){
  //---------------------------

  this->add_new_set("World");
  this->add_new_set("Scene");

eng::structure::Set* set = get_set("Scene");
set->add_new_set("coucou");
  //---------------------------
}
void Database::add_new_set(string name){
  //---------------------------

  eng::structure::Set* set = new eng::structure::Set(name);
  list_set.push_back(set);

  //---------------------------
}
eng::structure::Set* Database::get_set(string name){
  //---------------------------

  for(int i=0; i<list_set.size(); i++){
    eng::structure::Set* set = *next(list_set.begin(),i);
    if(set->name == name){
      return set;
    }
  }

  cout<<"[error] Set not found ["<<name<<"]"<<endl;

  //---------------------------
  return nullptr;
}
void Database::assign_ID(eng::structure::Entity* entity){
  //----------------------------

  if(entity->ID == -1){
    entity->ID = ID_entity++;
  }

  //----------------------------
}

}
