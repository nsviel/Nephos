#pragma once

#include <string>
#include <vector>


namespace utl::base{

struct Field{
  //---------------------------

  std::vector<float> data;
  std::string name = "";
  float min = 0;
  float max = 0;
  int size = -1;

  //---------------------------
};

}
