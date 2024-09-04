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
  //std::shared_ptr<utl::base::Pose> pose = std::make_shared<utl::base::Pose>();
  utl::base::Pose pose;

  virtual void info(){}

  //---------------------------
};

}
