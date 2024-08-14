#pragma once

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

class Exporter : public io::exporter::Base
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main function
  void export_data(io::exporter::Configuration& config, utl::base::Data* data);

  //Subfunction
  void build_structure(io::exporter::Configuration& config, utl::base::Data* data);
  void write_data_ascii(io::exporter::Configuration& config, std::ofstream& file, utl::base::Data* data);
  void write_data_binary(io::exporter::Configuration& config, std::ofstream& file, utl::base::Data* data);

private:
  fmt::ply::exporter::Header* io_header;
  utl::base::Attribut* utl_attribut;
};

}
