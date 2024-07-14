#pragma once


namespace ope::attribut{

struct Normal{
  //---------------------------

  float time = 0;
  bool enable = true;
  int knn = 4;

  //---------------------------
};

struct Intensity{
  //---------------------------


  //---------------------------
};

struct Structure{
  //---------------------------

  ope::attribut::Normal normal;
  ope::attribut::Intensity intensity;

  //---------------------------
};

}
