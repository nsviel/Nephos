#pragma once


namespace dyn::operation{

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

  dyn::operation::Normal normal;
  dyn::operation::Intensity intensity;

  //---------------------------
};

}
