#pragma once

#include <Kinect/Namespace.h>
#include <list>

namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}


namespace k4n::structure{

struct Device{
  //---------------------------

  int UID = 0;
  int nb_connected_sensor = 0;
  bool connected_device_change = false;
  k4n::dev::Master* selected_master = nullptr;
  std::list<k4n::dev::Master*> list_master;
  std::list<k4n::dev::Sensor*> list_sensor;

  //---------------------------
};

}
