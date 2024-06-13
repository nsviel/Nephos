#pragma once

#include <Loader/src/Format/PLY/Utils.h>
#include <Loader/src/Base/Exporter.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> //setprecision

namespace utl::base{class Pose;}


namespace format::ply{

class Exporter : public ldr::base::Exporter
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main function
  void export_ascii(utl::base::Data* data, glm::mat4 mat, std::string path);
  void export_binary(utl::base::Data* data, glm::mat4 mat, std::string path);

  //Subfunction
  void write_header(std::ofstream& file, std::string format, utl::base::Data* data);
  void write_data_ascii(std::ofstream& file, utl::base::Data* data, glm::mat4& mat);
  void write_data_binary(std::ofstream& file, utl::base::Data* data, glm::mat4& mat);

private:
  int property_number = 3;
  std::vector<int> vec_property;
};

}
