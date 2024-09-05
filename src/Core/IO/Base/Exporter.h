#pragma once

#include <Exporter/src/Structure/Configuration.h>
#include <Exporter/src/Structure/Enum.h>
#include <Utility/Base/Data/Data.h>
#include <vector>
#include <string>


namespace io::base{

struct Exporter{
  //---------------------------

  virtual void export_data(io::exp::Configuration& config, utl::base::Data& data){}

  std::vector<io::exp::Encoding> vec_encoding;
  std::string format = "";

  //---------------------------
};

}
