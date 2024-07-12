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
  void build_structure(fmt::ply::exporter::Structure& exporter, utl::base::Data* data);
  void write_data_ascii(fmt::ply::exporter::Structure& exporter, std::ofstream& file, utl::base::Data* data);
  void write_data_binary(fmt::ply::exporter::Structure& exporter, std::ofstream& file, utl::base::Data* data);

private:
  fmt::ply::exporter::Header* ldr_header;
};

}
