#pragma once

#include <Data/Base/Sensor/Namespace.h>


namespace dat::ply{

struct Structure{
  //---------------------------

  dat::base::sensor::Timestamp timestamp;
  dat::base::sensor::State state;

  //---------------------------
};

}
