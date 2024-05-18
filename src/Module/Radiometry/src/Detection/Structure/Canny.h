#pragma once


namespace rad::structure{

struct Canny{
  //---------------------------

  bool apply = false;
  int lower_threshold = 50;
  int upper_threshold = 150;

  //---------------------------
};

}
