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

  utl::base::Path path;
  float scaling = 1;
  bool with_centering = false;
  bool with_clearing = true;
  bool open_navigation = true;;

  //---------------------------
};

}
