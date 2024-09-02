#pragma once

#include <Utility/Base/Data/Pose.h>
#include <string>


namespace utl::base{

struct Element{
  //---------------------------

  int UID = -1;
  bool is_selectable = true;
  std::string name = "";
  std::string type = "";
  utl::base::Pose pose;

  virtual void info(){}

  //---------------------------
};

}
