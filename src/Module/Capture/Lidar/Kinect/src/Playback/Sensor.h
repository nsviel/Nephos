#pragma once

#include <Kinect/src/Device/Sensor.h>
#include <Dynamic/src/Base/Device.h>
#include <Utility/Specific/Common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/playback.hpp>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n::dev{class Sensor;}
namespace k4n::processing{class Data;}
namespace k4n::utils{class Configuration;}
namespace k4n::structure{class K4N;}


namespace k4n::playback{

class Sensor : public k4n::dev::Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n, string path);
  ~Sensor();

public:
  //Main function
  void thread_init();
  void thread_loop();
  void thread_end();

  //Subfunction
  k4a::capture* manage_new_capture();
  void manage_old_capture(k4a::capture* capture);
  void manage_pause();
  void manage_restart();
  void manage_ts_query(float ts_querry);

public:
  k4n::structure::Playback playback;
};


}
