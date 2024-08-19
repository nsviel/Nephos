#include "Field.h"

#include <Utility/Namespace.h>


namespace dat::atr{

//Constructor / Destructor
Field::Field(){
  //---------------------------


  //---------------------------
}
Field::~Field(){}

//Subfunction
std::vector<std::string> Field::get_field_names(utl::base::Data* data){
  std::vector<std::string> vec_name;
  //---------------------------

  std::vector<std::string> vec_field;
  for(int i=0; i<data->vec_field.size(); i++){
    utl::base::Field& field = data->vec_field[i];
    vec_name.push_back(field.name);
  }

  //---------------------------
  return vec_name;

}
std::vector<float>& Field::get_field_data(utl::base::Data* data, std::string name){
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
utl::base::Field* Field::get_field(utl::base::Data* data, std::string name){
  if(name == "") return nullptr;
  //---------------------------

  //Check if field is already present
  for(int i=0; i<data->vec_field.size(); i++){
    utl::base::Field& field = data->vec_field[i];
    if(field.name == name) return &field;
  }

  //---------------------------
  return nullptr;
}
glm::vec2 Field::get_field_range(utl::base::Data* data, std::string name){
  //---------------------------

  //Get data
  utl::base::Field* field = get_field(data, name);
  if(!field) return glm::vec2(0, 0);
  std::vector<float>& vec_data = field->data;
  if(vec_data.size() == 0) return glm::vec2(0, 0);

  //Get range
  float min = *std::min_element(vec_data.begin(), vec_data.end());
  float max = *std::max_element(vec_data.begin(), vec_data.end());
  glm::vec2 range = glm::vec2(min, max);

  //---------------------------
  return range;
}
void Field::set_field_data(utl::base::Data* data, std::string name, std::vector<float>& vec){
  if(vec.size() == 0) return;
  //---------------------------

  this->create_field(data, name);
  utl::base::Field* field = get_field(data, name);
  if(!field) return;

  field->data = vec;

  //---------------------------
}
void Field::create_field(utl::base::Data* data, std::string name){
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
