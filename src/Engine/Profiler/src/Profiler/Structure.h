#pragma once

#include <Utility/Specific/Common.h>


namespace prf{

struct Structure{
  //---------------------------
  
  virtual void clean(){}
  virtual void show_info(){}

  string name = "";
  string type = "";

  //---------------------------
};

}
