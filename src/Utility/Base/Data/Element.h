#pragma once

#include <Utility/Base/Data/Pose.h>
#include <string>


namespace utl::element{

enum Type{
  DATA = 0,
  SET = 1,
  ENTITY = 2,
};

}

namespace utl::base{

struct Element{
  //---------------------------

  int UID = -1;
  int type = 0;
  bool is_selectable = true;
  std::string name = "";
  utl::base::Pose pose;

  virtual void info(){}

  //---------------------------
};

}