#pragma once

#include <string>
#include <Utility/Base/Type/Pose.h>


namespace utl::base{

struct Element{
  //---------------------------

  int UID = -1;
  bool is_selectable = true;
  std::string name = "";
  utl::base::Pose pose;

  virtual void info(){}

  //---------------------------
};

}
