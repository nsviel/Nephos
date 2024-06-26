#pragma once

#include <string>


namespace prf{

struct Structure{
  //---------------------------

  virtual void clean(){}
  virtual void show_info(){}

  std::string name = "";
  std::string type = "";

  //---------------------------
};

}
