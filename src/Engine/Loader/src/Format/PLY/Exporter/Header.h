#pragma once

#include <Loader/src/Format/PLY/Structure/Namespace.h>
#include <Loader/src/Base/Exporter.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> //setprecision

namespace utl::base{class Pose;}


namespace format::ply::exporter{

class Header
{
public:
  //Constructor / Destructor
  Header();
  ~Header();

public:
  //Main function
  void write_header(std::ofstream& file, std::string format, utl::base::Data* data);

  //Subfunction
  void write_info(std::ofstream& file, std::string& format, utl::base::Data* data);
  void write_property_xyz(std::ofstream& file);
  void write_property_attribut(std::ofstream& file, utl::base::Data* data);

private:
  int property_number = 3;
  std::vector<int> vec_property;
};

}
