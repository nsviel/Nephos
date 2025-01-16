#include "Manager.h"

#include <Utility/Namespace.h>


namespace dat::atr::field{

//Constructor / Destructor
Manager::Manager(){
  //---------------------------


  //---------------------------
}
Manager::~Manager(){}

//Main function
std::vector<std::string> Manager::get_field_names(utl::base::Data& data){
  std::vector<std::string> vec_name;
  //---------------------------

  for(auto& [name, field] : data.map_field){
    vec_name.push_back(name);
  }

  //---------------------------
  return vec_name;

}
std::vector<float>& Manager::get_field_data(utl::base::Data& data, const std::string& name){
  //---------------------------

  auto field = get_field(data, name);

  // Check if field is nullptr
  if(!field){
    static std::vector<float> empty_vector;
    return empty_vector;
  }

  //---------------------------
  return field->data;
}
glm::vec2 Manager::get_field_range(utl::base::Data& data, const std::string& name){
  //---------------------------

  //Get data
  auto field = get_field(data, name);
  if(!field || field->data.empty()){
    return glm::vec2(0, 0);
  }

  //Get range
  float min = *std::min_element(field->data.begin(), field->data.end());
  float max = *std::max_element(field->data.begin(), field->data.end());

  //---------------------------
  return glm::vec2(min, max);
}
void Manager::set_field_data(utl::base::Data& data, const std::string& name, std::vector<float>& vec){
  if(vec.size() == 0) return;
  //---------------------------

  this->create_field(data, name);
  auto field = get_field(data, name);
  if(field) field->data = vec;

  //---------------------------
}

//Subfunction
void Manager::create_field(utl::base::Data& data, const std::string& name){
  if(is_field_exists(data, name)) return;
  //---------------------------

  std::shared_ptr<utl::base::Field> new_field = std::make_shared<utl::base::Field>();
  new_field->name = name;
  data.map_field[name] = new_field;

  //---------------------------
}
bool Manager::is_field_exists(utl::base::Data& data, const std::string& name){
  //---------------------------

  auto it = data.map_field.find(name);
  if (it == data.map_field.end()) {
    return false;
  } else {
    return true;
  }

  //---------------------------
}
std::shared_ptr<utl::base::Field> Manager::get_field(utl::base::Data& data, const std::string& name){
  //---------------------------

  auto it = data.map_field.find(name);
  if (it == data.map_field.end()) {
    return nullptr;
  } else {
    return it->second;
  }

  //---------------------------
}

}
