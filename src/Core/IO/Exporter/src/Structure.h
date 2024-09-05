#pragma once

#include <Exporter/src/Structure/Operation.h>
#include <Exporter/src/Structure/Enum.h>
#include <Utility/Base/Data/Path.h>
#include <string>


namespace io::exp{

struct Structure{
  //---------------------------

  Structure(){
    path.directory = utl::path::get_current_directory_path();
    path.format = ".ply";
  }

  io::exp::structure::Operation operation;
  io::exp::Encoding encoding = io::exp::BINARY;
  utl::base::Path path;

  //---------------------------
};

}
