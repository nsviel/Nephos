#pragma once

#include <IO/src/Export/Structure/Base.h>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip> //setprecision

namespace utl::base{class Pose;}


namespace fmt::ply::exporter{

class Header
{
public:
  //Constructor / Destructor
  Header();
  ~Header();

public:
  //Main function
  void write_header(io::exporter::Configuration& config, std::ofstream& file);

  //Subfunction
  void write_info(io::exporter::Configuration& config, std::ofstream& file);
  void write_property(io::exporter::Configuration& config, std::ofstream& file);
  void write_end(std::ofstream& file);

private:

};

}
