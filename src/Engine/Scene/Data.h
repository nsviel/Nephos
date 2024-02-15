#pragma once

#include <Utility/Specific/common.h>


namespace eng::scene{

struct Loader_data{
  //---------------------------

  vector<string> supported_format;

  //---------------------------
};

struct Data{
  //---------------------------

  Loader_data loader;

  //---------------------------
};

}
