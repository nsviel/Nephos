#pragma once


namespace rad::cor::structure{

struct Canny{
  //---------------------------

  bool apply = false;
  int thres_lower = 50;
  int thres_upper = 150;

  //---------------------------
};

}
