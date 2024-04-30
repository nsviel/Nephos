#pragma once


namespace utl::type{

struct Element{
  //---------------------------

  int UID = -1;
  bool is_selectable = true;
  virtual void hello(){}

  //---------------------------
};

}
