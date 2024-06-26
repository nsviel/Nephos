#pragma once

#include <string>


namespace prf::base{

enum Type{
  GRAPH = 0,
  HARDWARE = 1,
  VULKAN = 2,
};

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
