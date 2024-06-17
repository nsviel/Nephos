#pragma once

#include <string>
#include <vector>


namespace rad::calibration::structure{

struct Plot{
  //---------------------------

  utl::base::Plot IfR;
  utl::base::Plot IfIt;
  utl::base::Plot IfRIt;

  //---------------------------
};

}
