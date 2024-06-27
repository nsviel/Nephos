#pragma once

#include <Utility/Specific/Common.h>


namespace utl::gui{

struct Panel{
  //---------------------------

  Panel(const string& n, const string& i, bool o) : name(n), icon(i), is_open(o){}

  std::string name;
  std::string icon;
  bool is_open;

  //---------------------------
};

}
