#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>

namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}




namespace k4n::structure{

struct K4N{
  //---------------------------

  int kinect_num_connection = 0;
  bool kinect_connection_state = false;
  std::list<k4n::dev::Master*> list_master;
  std::list<k4n::dev::Sensor*> list_sensor;

  //---------------------------
};

}
