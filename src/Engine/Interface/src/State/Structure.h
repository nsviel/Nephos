#pragma once

#include <Utility/Base/Data/Path.h>
#include <string>
#include <vector>


namespace itf::state{

struct Structure{
  //---------------------------

  std::vector<std::string> vec_file;
  utl::base::Path path_default;
  utl::base::Path path_current;
  utl::base::Path path_save;
  bool flag_reload = false;

  //---------------------------
};

}
