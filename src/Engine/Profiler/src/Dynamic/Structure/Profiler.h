#pragma once

#include <string>


namespace prf::dynamic{

struct Profiler{
  //---------------------------

  virtual void clean(){}
  virtual void show_info(){}
  void set_name(std::string value){this->name = value;}

  std::string name = "";
  int type = -1;

  //---------------------------
};

}
