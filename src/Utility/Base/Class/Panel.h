#pragma once

#include <string>


namespace utl::gui{

struct Panel{
  //---------------------------

  Panel(const std::string& name, const std::string& icon, bool open){
    this->name = name;
    this->icon = icon;
    this->is_open = open;
  }

  std::string name;
  std::string icon;
  bool is_open;

  //---------------------------
};

}
