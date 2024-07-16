#pragma once

#include <vector>
#include <string>

namespace utl::base{class Data;}
namespace utl::base{class Field;}


namespace utl::base{

class Attribut
{
public:
  Attribut();
  ~Attribut();

public:
  //Main function
  void set_field_data(utl::base::Data* data, std::string name, std::vector<float>& vec);
  void create_field(utl::base::Data* data, std::string name);
  std::vector<float>& get_field_data(utl::base::Data* data, std::string name);
  utl::base::Field* get_field(utl::base::Data* data, std::string name);

private:
};

}
