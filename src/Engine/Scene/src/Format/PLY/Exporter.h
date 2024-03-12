#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace format::ply{

enum Attribut{
  EMPTY = 0,
  XYZ = 1,
  RGB = 2,
  N = 3,
  I = 4,
  TS = 5,
};

class Exporter : public utl::type::Exporter
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main functions
  void export_ascii(utl::type::Data* data, std::string path);
  void export_binary(utl::type::Data* data, std::string path);

  //Subfunction
  void write_header(std::ofstream& file, std::string format, utl::type::Data* data);
  void write_data_ascii(std::ofstream& file, utl::type::Data* data);
  void write_data_binary(std::ofstream& file, utl::type::Data* data);

private:
  int property_number = 3;
  vector<int> vec_property;
};

}
