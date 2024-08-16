#pragma once

#include <Kinect/src/Structure/Firmware.h>
#include <Kinect/src/Structure/Namespace.h>
#include <Kinect/src/Structure/Cloud.h>
#include <Processing/src/Base/Sensor.h>
#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>
#include <glm/glm.hpp>

namespace k4n::device{class Structure;}
namespace k4n::color{class Structure;}
namespace k4n::depth{class Structure;}
namespace k4n::infrared{class Structure;}
namespace k4n::imu{class Structure;}


namespace k4n::base{

struct Sensor : public dyn::prc::base::Sensor{
  //---------------------------

  Sensor();
  ~Sensor();
  void clean();
  glm::vec3 convert_depth_2d_to_3d(glm::ivec2 point_2d);

  k4n::structure::Cloud cloud;
  k4n::device::Structure device;
  k4n::color::Structure color;
  k4n::depth::Structure depth;
  k4n::infrared::Structure ir;
  k4n::imu::Structure imu;
  k4n::firmware::Structure firmware;
  k4n::structure::FPS fps;

  //---------------------------
};

}
