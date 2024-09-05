#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>

#include "Enum.h"


namespace io::exp{

struct Structure{
  //---------------------------

  Structure(){
    path.directory = utl::path::get_current_directory_path();
    path.format = ".ply";
  }
  
  io::exp::Encoding encoding = io::exp::BINARY;
  utl::base::Path path;
  bool with_transformation = false;
  bool with_colorization = false;

  //---------------------------
};

}
