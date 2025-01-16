#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

namespace utl::base{class Data;}
namespace utl::base{class Field;}


namespace dat::atr::field{

class Manager
{
public:
  Manager();
  ~Manager();

public:
  //Main function
  std::vector<std::string> get_field_names(utl::base::Data& data);
  std::vector<float>& get_field_data(utl::base::Data& data, const std::string& name);
  glm::vec2 get_field_range(utl::base::Data& data, const std::string& name);
  void set_field_data(utl::base::Data& data, const std::string& name, std::vector<float>& vec);

private:
  //Subfunction
  void create_field(utl::base::Data& data, const std::string& name);
  bool is_field_exists(utl::base::Data& data, const std::string& name);
  std::shared_ptr<utl::base::Field> get_field(utl::base::Data& data, const std::string& name);

private:

};

}
