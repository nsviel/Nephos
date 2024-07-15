#pragma once

#include <IO/src/Format/PLY/Structure/Namespace.h>
#include <IO/src/Export/Structure/Base.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> //setprecision

namespace utl::base{class Pose;}
namespace utl::base{class Attribut;}
namespace fmt::ply::exporter{class Header;}


namespace fmt::ply{

class Exporter : public ldr::exporter::Base
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main function
  void export_data(ldr::exporter::Configuration& config, utl::base::Data* data);

  //Subfunction
  void build_structure(fmt::ply::exporter::Structure& exporter, utl::base::Data* data);
  void write_data_ascii(fmt::ply::exporter::Structure& exporter, std::ofstream& file, utl::base::Data* data);
  void write_data_binary(fmt::ply::exporter::Structure& exporter, std::ofstream& file, utl::base::Data* data);

private:
  fmt::ply::exporter::Header* ldr_header;
  utl::base::Attribut* utl_attribut;
};

}
