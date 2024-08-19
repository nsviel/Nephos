#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace utl::base{class Data;}
namespace utl::base{class Field;}


namespace dat::atr{

class Field
{
public:
  Field();
  ~Field();

public:
  //Main function
  std::vector<std::string> get_field_names(utl::base::Data* data);
  std::vector<float>& get_field_data(utl::base::Data* data, std::string name);
  utl::base::Field* get_field(utl::base::Data* data, std::string name);
  glm::vec2 get_field_range(utl::base::Data* data, std::string name);
  void set_field_data(utl::base::Data* data, std::string name, std::vector<float>& vec);
  void create_field(utl::base::Data* data, std::string name);

private:
};

}
