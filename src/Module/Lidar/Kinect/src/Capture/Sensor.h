#pragma once

#include <Kinect/src/Structure/Sensor.h>
#include <Utility/Specific/Common.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>

namespace eng{class Node;}
namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::dev{class Sensor;}
namespace k4n::gui{class Capture;}
namespace k4n::processing{class Data;}
namespace k4n::utils{class Configuration;}
namespace k4n::structure{class K4N;}


namespace k4n::capture{

class Sensor : public k4n::dev::Sensor
{
public:
  //Constructor / Destructor
  Sensor(k4n::Node* node_k4n, int index);
  ~Sensor();

public:
  //Main function
  void info();
  void thread_init();
  void thread_loop();
  void thread_end();

  //Subfunction
  k4a::capture* manage_new_capture();
  void manage_old_capture(k4a::capture* capture);
  void manage_pause();
  void manage_reset();
  void manage_configuration();
  vec3 convert_depth_2d_to_3d(ivec2 point_2d);

private:
  k4n::processing::Image* k4n_image;
  k4n::utils::Configuration* k4n_config;
  k4n::gui::Capture* gui_capture;
  k4n::Structure* k4n_struct;

  bool is_recording = false;
};


}
