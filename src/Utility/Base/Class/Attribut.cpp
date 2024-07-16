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
std::vector<float>& Attribut::get_field_data(utl::base::Data* data, std::string name){
  //---------------------------

  utl::base::Field* field = get_field(data, name);

  // Check if field is nullptr
  if(!field){
    static std::vector<float> empty_vector;
    return empty_vector;
  }

  //---------------------------
  return field->data;
}
utl::base::Field* Attribut::get_field(utl::base::Data* data, std::string name){
  //---------------------------

  //Check if field is already present
  for(int i=0; i<data->vec_field.size(); i++){
    utl::base::Field& field = data->vec_field[i];
    if(field.name == name) return &field;
  }

  //If not found, create it
  this->create_field(data, name);

  //Remade research
  for(int i=0; i<data->vec_field.size(); i++){
    utl::base::Field& field = data->vec_field[i];
    if(field.name == name) return &field;
  }

  //---------------------------
  return nullptr;
}
glm::vec2 Attribut::get_field_range(utl::base::Data* data, std::string name){
  //---------------------------

  //Get data
  utl::base::Field* field = get_field(data, name);
  std::vector<float>& vec_data = field->data;
  if(vec_data.size() == 0) return glm::vec2(0, 0);

  //Get range
  float min = *std::min_element(vec_data.begin(), vec_data.end());
  float max = *std::max_element(vec_data.begin(), vec_data.end());
  glm::vec2 range = glm::vec2(min, max);

  //---------------------------
  return range;
}
void Attribut::set_field_data(utl::base::Data* data, std::string name, std::vector<float>& vec){
  //---------------------------

  utl::base::Field* field = get_field(data, name);

  if(field){
    field->data = vec;
  }

  //---------------------------
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



}
