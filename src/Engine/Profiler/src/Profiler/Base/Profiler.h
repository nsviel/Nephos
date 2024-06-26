#pragma once

#include <string>


namespace prf::base{

struct Profiler{
  //---------------------------

  virtual void clean(){}
  virtual void show_info(){}

  std::string name = "";
  std::string type = "";

  //---------------------------
};

}
