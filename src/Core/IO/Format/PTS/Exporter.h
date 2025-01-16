#pragma once

#include <IO/Base/Exporter.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>

namespace dat::atr::field{class Manager;}


namespace fmt::pts{

class Exporter : public io::base::Exporter
{
public:
  //Constructor / Destructor
  Exporter();
  ~Exporter();

public:
  //Main function
  void export_data(io::exp::Configuration& config, utl::base::Data& data);

  //Subfunction
  void write_data_ascii(io::exp::Configuration& config, utl::base::Data& data);

private:
  dat::atr::field::Manager* atr_field;
};

}
