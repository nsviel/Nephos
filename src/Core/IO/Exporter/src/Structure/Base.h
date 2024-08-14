#pragma once

#include <Utility/Base/Data/Data.h>
#include <vector>
#include <string>

#include "Enum.h"
#include "Configuration.h"


namespace io::exp{

struct Base{
  //---------------------------

  virtual void export_data(io::exp::Configuration& config, utl::base::Data* data){}

  std::vector<io::exp::Encoding> vec_encoding;
  std::string format = "";

  //---------------------------
};

}
