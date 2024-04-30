#pragma once

#include <Loader/src/Base/Exporter.h>
#include <Utility/Function/File/Path.h>
#include <Utility/Base/Type/Pose.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> //setprecision


namespace format::ply{

enum Attribut{
  EMPTY = 0,
  XYZ = 1,
  RGB = 2,
  N = 3,
  I = 4,
  TS = 5,
};

class Exporter : public ldr::base::Exporter
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main functions
  void export_ascii(utl::type::Data* data, std::string path);
  void export_binary(utl::type::Data* data, utl::type::Pose* pose, std::string path);

  //Subfunction
  void write_header(std::ofstream& file, std::string format, utl::type::Data* data);
  void write_data_ascii(std::ofstream& file, utl::type::Data* data);
  void write_data_binary(std::ofstream& file, utl::type::Data* data, utl::type::Pose* pose);

private:
  int property_number = 3;
  std::vector<int> vec_property;
};

}
