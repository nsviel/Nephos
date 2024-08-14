#pragma once

#include <IO/src/Export/Structure/Base.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>

namespace utl::base{class Attribut;}


namespace fmt::pts{

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
  void write_data_ascii(io::exporter::Configuration& config, utl::base::Data* data);

private:
  utl::base::Attribut* utl_attribut;
};

}
