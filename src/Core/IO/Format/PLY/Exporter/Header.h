#pragma once

#include <IO/Base/Exporter.h>
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
  void write_header(io::exp::Configuration& config, std::ofstream& file);

  //Subfunction
  void write_info(io::exp::Configuration& config, std::ofstream& file);
  void write_property(io::exp::Configuration& config, std::ofstream& file);
  void write_end(std::ofstream& file);

private:

};

}
