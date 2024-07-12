#pragma once

#include <string>
#include <vector>


namespace utl::base::data{

struct Attribut{
  //---------------------------

  std::vector<float> data;
  std::string name = "";
  int size = -1;

  //---------------------------
};

}
