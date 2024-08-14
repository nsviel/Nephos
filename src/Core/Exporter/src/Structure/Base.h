#pragma once

#include <IO/src/Export/Structure/Enum.h>
#include <IO/src/Export/Structure/Configuration.h>
#include <Utility/Base/Data/Data.h>
#include <vector>
#include <string>


namespace io::exporter{

struct Base{
  //---------------------------

  virtual void export_data(io::exporter::Configuration& config, utl::base::Data* data){}

  std::vector<io::exporter::Encoding> vec_encoding;
  std::string format = "";

  //---------------------------
};

}
