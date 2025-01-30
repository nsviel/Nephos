#pragma once

#include <Exporter/src/Structure/Configuration.h>
#include <Exporter/src/Structure/Enum.h>
#include <IO/Base/Format.h>
#include <Utility/Base/Data/Data.h>
#include <vector>


namespace io::base{

struct Exporter{
  //---------------------------

  virtual void export_data(io::exp::Configuration& config, utl::base::Data& data){}

  std::vector<io::exp::Encoding> vec_encoding;
  io::base::Format format;

  //---------------------------
};

}
