#pragma once

#include <Data/Sensor/Structure/Namespace.h>


namespace dat::ply{

struct Structure{
  //---------------------------

  dat::sensor::Timestamp timestamp;
  dat::sensor::State state;

  //---------------------------
};

}
