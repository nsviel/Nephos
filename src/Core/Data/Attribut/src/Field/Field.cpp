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
std::vector<std::string> Field::get_field_names(utl::base::Data& data){
  std::vector<std::string> vec_name;
  //---------------------------

  for(const auto& field : data.vec_field){
    vec_name.push_back(field.name);
  }

  //---------------------------
  return vec_name;

}
std::unique_ptr<std::vector<float>> Field::get_field_data(utl::base::Data& data, const std::string& name){
  //---------------------------

  auto field = get_field(data, name);

  // Check if field is nullptr
  if(!field) return std::make_unique<std::vector<float>>();

  //---------------------------
  return std::make_unique<std::vector<float>>(field->data);
}
glm::vec2 Field::get_field_range(utl::base::Data& data, const std::string& name){
  //---------------------------

  //Get data
  auto field = get_field(data, name);
  if (!field || field->data.empty()) {
    return glm::vec2(0, 0);
  }

  //Get range
  float min = *std::min_element(field->data.begin(), field->data.end());
  float max = *std::max_element(field->data.begin(), field->data.end());

  //---------------------------
  return glm::vec2(min, max);
}
void Field::set_field_data(utl::base::Data& data, const std::string& name, std::vector<float>& vec){
  if(vec.size() == 0) return;
  //---------------------------

  this->create_field(data, name);
  auto field = get_field(data, name);
  if(field) field->data = vec;

  //---------------------------
}
void Field::create_field(utl::base::Data& data, const std::string& name){
  //---------------------------

  //Check if field is already present
  if (std::any_of(data.vec_field.begin(), data.vec_field.end(), [&](const auto& field) { return field.name == name; })) {
    return;
  }

  //Create it
  utl::base::Field field;
  field.name = name;
  data.vec_field.push_back(field);

  //---------------------------
}

//Subfunction
std::shared_ptr<utl::base::Field> Field::get_field(utl::base::Data& data, const std::string& name){
  //---------------------------

  auto it = std::find_if(data.vec_field.begin(), data.vec_field.end(), [&](const auto& field) { return field.name == name; });
  if (it != data.vec_field.end()) {
    return std::make_shared<utl::base::Field>(*it);
  }

  //---------------------------
  return nullptr;
}

}
