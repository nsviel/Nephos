#pragma once

#include <Data/Sensor/Structure/Namespace.h>


namespace dat::ply{

struct Structure{
  //---------------------------

  dat::base::sensor::Timestamp timestamp;
  dat::base::sensor::State state;

  //---------------------------
};

}
