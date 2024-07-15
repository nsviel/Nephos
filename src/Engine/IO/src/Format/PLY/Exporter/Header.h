#pragma once

#include <IO/src/Format/PLY/Structure/Namespace.h>
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
  void write_header(fmt::ply::exporter::Structure& exporter, std::ofstream& file);

  //Subfunction
  void write_info(fmt::ply::exporter::Structure& exporter, std::ofstream& file);
  void write_property(fmt::ply::exporter::Structure& exporter, std::ofstream& file);
  void write_end(std::ofstream& file);

private:

};

}
