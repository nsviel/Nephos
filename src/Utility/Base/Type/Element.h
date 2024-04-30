#pragma once

#include <string>


namespace utl::type{

struct Element{
  //---------------------------

  int UID = -1;
  bool is_selectable = true;
  std::string name = "";

  virtual void hello(){}

  //---------------------------
};

}
