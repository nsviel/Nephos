#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>


namespace io::imp{

struct Structure{
  //---------------------------

  Structure(){
    path.directory = utl::path::get_current_directory_path();
    path.format = ".ply";
  }

  io::imp::structure::Operation operation;
  std::vector<io::base::Importer*> vec_importer;
  utl::base::Path path;

  //---------------------------
};

}
