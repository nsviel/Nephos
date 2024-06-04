#pragma once

#include <Utility/Specific/Common.h>


namespace prf{

struct Structure{
  //---------------------------

  Structure(string name, string type){
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
