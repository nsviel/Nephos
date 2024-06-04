#pragma once

#include <Kinect/src/Structure/Namespace.h>
#include <Dynamic/src/Base/Sensor.h>
#include <Utility/Namespace.h>

namespace k4n::device{class Structure;}
namespace k4n::color{class Structure;}
namespace k4n::depth{class Structure;}
namespace k4n::infrared{class Structure;}
namespace k4n::imu{class Structure;}
namespace k4n::structure{class FPS;}


namespace k4n::dev{

struct Sensor : public dyn::base::Sensor{
  //---------------------------

  k4n::device::Structure device;
  k4n::color::Structure color;
  k4n::depth::Structure depth;
  k4n::infrared::Structure ir;
  k4n::imu::Structure imu;
  k4n::structure::FPS fps;

  float ts_beg = -1;
  float ts_end = -1;
  float ts_duration = -1;

  //---------------------------
};

}
