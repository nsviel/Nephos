#pragma once


namespace dyn::prc::operation{

struct Normal{
  //---------------------------

  float time = 0;
  bool enable = true;
  int knn = 4;

  //---------------------------
};

struct Intensity{
  //---------------------------

  int diviser = 1000;

  //---------------------------
};

struct Structure{
  //---------------------------

  dyn::prc::operation::Normal normal;
  dyn::prc::operation::Intensity intensity;

  //---------------------------
};

}
