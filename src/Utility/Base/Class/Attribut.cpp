#include "Attribut.h"

#include <Utility/Namespace.h>


namespace utl::base{

//Constructor / Destructor
Attribut::Attribut(){
  //---------------------------


  //---------------------------
}
Attribut::~Attribut(){}

//Subfunction
void Attribut::set_field_data(utl::base::Data* data, std::string name, std::vector<float>& vec){
  //---------------------------

  this->create_field(data, name);
  utl::base::Field* field = get_field(data, name);

  if(field){
    field->data = vec;
  }

  //---------------------------
}
std::vector<float>& Attribut::get_field_data(utl::base::Data* data, std::string name){
  //---------------------------

  this->create_field(data, name);
  utl::base::Field* field = get_field(data, name);

  // Check if field is nullptr
  if(!field){
    static std::vector<float> empty_vector;
    return empty_vector;
  }

  //---------------------------
  return field->data;
}
void Attribut::create_field(utl::base::Data* data, std::string name){
  //---------------------------

  //Check if field is already present
  for(int i=0; i<data->vec_field.size(); i++){
    utl::base::Field& field = data->vec_field[i];
    if(field.name == name) return;
  }

  //Create it
  utl::base::Field field;
  field.name = name;
  data->vec_field.push_back(field);

  //---------------------------
}
utl::base::Field* Attribut::get_field(utl::base::Data* data, std::string name){
  //---------------------------

  //Check if field is already present
  for(int i=0; i<data->vec_field.size(); i++){
    utl::base::Field& field = data->vec_field[i];
    if(field.name == name) return &field;
  }

  //---------------------------
  return nullptr;
}


}
