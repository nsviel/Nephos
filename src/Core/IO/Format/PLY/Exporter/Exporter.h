#pragma once

#include <Exporter/src/Structure/Base.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> //setprecision

namespace utl::base{class Pose;}
namespace dat::atr{class Field;}
namespace fmt::ply::exporter{class Header;}


namespace fmt::ply{

class Exporter : public io::exp::Base
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main function
  void export_data(io::exp::Configuration& config, utl::base::Data* data);

  //Subfunction
  void build_structure(io::exp::Configuration& config, utl::base::Data* data);
  void write_data_ascii(io::exp::Configuration& config, std::ofstream& file, utl::base::Data* data);
  void write_data_binary(io::exp::Configuration& config, std::ofstream& file, utl::base::Data* data);

private:
  fmt::ply::exporter::Header* io_header;
  dat::atr::Field* atr_field;
};

}
