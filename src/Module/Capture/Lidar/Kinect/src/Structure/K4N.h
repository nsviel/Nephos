#pragma once

#include <Utility/Specific/Common.h>
#include <Radiometry/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>

namespace k4n::dev{class Master;}
namespace k4n::dev{class Sensor;}


namespace k4n::color{

enum Mode{
  CAMERA = 0,
  UNICOLOR = 1,
  INTENSITY = 2,
  HEATMAP = 3,
  STRUCTURE = 4,
};

}

namespace k4n::structure{

struct K4N{
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
