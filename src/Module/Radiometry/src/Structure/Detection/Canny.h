#pragma once


namespace radio::structure{

struct Canny{
  //---------------------------

  bool apply = false;
  int lower_threshold = 50;
  int upper_threshold = 150;

  //---------------------------
};

}
