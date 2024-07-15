#pragma once

#include <vector>
#include <string>

namespace utl::base{class Data;}
namespace utl::base::data{class Attribut;}


namespace utl::base{

class Attribut
{
public:
  Attribut();
  ~Attribut();

public:
  //Main function
  void set_attribut_data(utl::base::Data* data, std::string name, std::vector<float>& vec);
  void create_attribut(utl::base::Data* data, std::string name);
  std::vector<float>& get_attribut_data(utl::base::Data* data, std::string name);
  utl::base::data::Attribut* get_attribut(utl::base::Data* data, std::string name);

private:
};

}
