#pragma once

#include <Data/Namespace.h>
#include <Utility/Specific/Common.h>
#include <Kinect/src/Structure/Namespace.h>
#include <Dynamic/src/Base/Sensor.h>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace k4n::processing{class Image;}
namespace k4n::utils{class Configuration;}
namespace k4n::capture{class Sensor;}
namespace k4n::playback{class Sensor;}
namespace k4n::device{class Structure;}
namespace k4n::structure{class Playback;}
namespace k4n::structure{class Recorder;}
namespace k4n::color{class Structure;}
namespace k4n::depth{class Structure;}
namespace k4n::infrared{class Structure;}
namespace k4n::imu{class Structure;}
namespace k4n::structure{class Calibration;}
namespace k4n::structure{class FPS;}
namespace prf::graph{class Profiler;}
namespace dat::base{class Object;}


namespace k4n::dev{

class Sensor : public dat::base::Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n);
  ~Sensor();

public:
  //Main function
  void init();
  void clean();

public:
  prf::graph::Profiler* profiler;


  k4n::device::Structure device;
  k4n::color::Structure color;
  k4n::depth::Structure depth;
  k4n::infrared::Structure ir;
  k4n::imu::Structure imu;
  k4n::structure::FPS fps;

  float ts_beg = -1;
  float ts_end = -1;
  float ts_duration = -1;

protected:
  eng::Node* node_engine;
};

}
