#pragma once

#include <Utility/Specific/common.h>


namespace prf::type{

struct Profiler{
  //---------------------------

  Profiler(string name, string type){
    //---------------------------

    this->name = name;
    this->type = type;

    //---------------------------
  }
  virtual void clean(){}
  virtual void show_info(){}

  inline std::string get_name(){return name;}
  inline std::string get_type(){return type;}

  string name;
  string type;

  //---------------------------
};

}
