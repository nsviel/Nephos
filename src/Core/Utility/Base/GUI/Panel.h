#pragma once

#include <string>


namespace utl::gui{

struct Panel{
  //---------------------------

  Panel(const std::string& n, const std::string& i, bool o) : name(n), icon(i), is_open(o){}

  std::string name;
  std::string icon;
  bool is_open;

  //---------------------------
};

}
