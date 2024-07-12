#pragma once

#include <Loader/src/Format/PLY/Structure/Namespace.h>
#include <Loader/src/Base/Exporter.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> //setprecision

namespace utl::base{class Pose;}
namespace fmt::ply::exporter{class Header;}


namespace fmt::ply{

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
  void find_vec_property(utl::base::Data* data);
  void write_header(std::ofstream& file, std::string format, utl::base::Data* data);
  void write_data_ascii(std::ofstream& file, utl::base::Data* data, glm::mat4& mat);
  void write_data_binary(std::ofstream& file, utl::base::Data* data, glm::mat4& mat);

private:
  fmt::ply::exporter::Header* ldr_header;

  int property_number = 3;
  std::vector<int> vec_property;
};

}
