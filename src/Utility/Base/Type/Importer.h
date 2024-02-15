#pragma once

#include <Utility/Specific/common.h>


namespace utl::type{

struct Importer
{
  //---------------------------

  virtual void import(string path);
  
  vector<string> supported_format;

  //---------------------------
};

}
