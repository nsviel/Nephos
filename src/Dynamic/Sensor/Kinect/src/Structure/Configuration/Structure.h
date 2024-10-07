#pragma once

#include <Kinect/src/Structure/Configuration/FPS.h>
#include <Kinect/src/Structure/Configuration/Synchro.h>
#include <Kinect/src/Structure/Data/Color/Configuration.h>
#include <Kinect/src/Structure/Data/Depth/Configuration.h>
#include <Kinect/src/Structure/Data/Infrared/Configuration.h>
#include <Kinect/src/Structure/Camera/Structure.h>


namespace k4n::str::config{

struct Structure{
  //---------------------------

  k4n::str::depth::Configuration depth;
  k4n::str::color::Configuration color;
  k4n::str::infra::Configuration ir;

  k4n::str::camera::Structure camera;
  k4n::str::config::Synchro synchro;
  k4n::str::config::FPS fps;

  //---------------------------
};

}
