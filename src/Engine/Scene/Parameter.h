#pragma once

#include <Utility/Specific/common.h>


namespace eng::scene{

struct Parameter : public utl::type::Parameter{
  //---------------------------

  string path_current_dir;
  vector<string> supported_format;

  //---------------------------
};

}
