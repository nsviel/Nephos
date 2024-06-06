#pragma once

#include <Utility/Specific/Common.h>
#include <Operation/Namespace.h>
#include <cstdint>


namespace dyn::operation{

struct Normal{
  //---------------------------

  bool enable = true;
  float time = 0;
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
