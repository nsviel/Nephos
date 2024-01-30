#pragma once

#include <Utility/Specific/common.h>


namespace utl::gui{

struct Panel{
  //---------------------------

  Panel(const string& n, const string& i, bool o) : name(n), icon(i), is_open(o){}

  string name;
  string icon;
  bool is_open;

  //---------------------------
};

}
