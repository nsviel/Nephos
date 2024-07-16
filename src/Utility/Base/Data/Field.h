#pragma once

#include <string>
#include <vector>


namespace utl::base{

struct Field{
  //---------------------------

  std::vector<float> data;
  std::string name = "";
  int size = -1;

  //---------------------------
};

}
