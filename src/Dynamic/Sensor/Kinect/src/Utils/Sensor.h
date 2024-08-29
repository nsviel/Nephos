#pragma once

#include <Kinect/src/Structure/Firmware.h>
#include <Kinect/src/Structure/Namespace.h>
#include <Kinect/src/Structure/Cloud.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>

namespace k4n::device{class Structure;}
namespace k4n::color{class Structure;}
namespace k4n::depth{class Structure;}
namespace k4n::infrared{class Structure;}
namespace k4n::imu{class Structure;}


namespace k4n::base{

struct Sensor : public dat::base::Sensor{
  //---------------------------

  Sensor(){
    this->info.model = "kinect";
    this->info.depth_mode = "NFOV";
    this->info.vec_depth_mode.push_back("NFOV");
    this->info.vec_depth_mode.push_back("WFOV");

    this->data.topology.type = utl::topology::POINT;
    this->data.nb_data_max = 10000000;
    this->calibration.path.insert("../media/calibration/kinect.json");
  }
  void start(){
    this->start_thread();
  }
  void stop(){
    this->stop_thread();
  }

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
