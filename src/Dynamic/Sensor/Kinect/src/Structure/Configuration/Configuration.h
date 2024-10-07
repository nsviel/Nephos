#pragma once

#include <Kinect/src/Structure/Configuration/FPS.h>
#include <Kinect/src/Structure/Configuration/Synchro.h>
#include <Kinect/src/Structure/Data/Color/Configuration.h>
#include <Kinect/src/Structure/Data/Depth/Configuration.h>
#include <Kinect/src/Structure/Data/Infrared/Configuration.h>
#include <Kinect/src/Structure/Configuration/Camera.h>


namespace k4n::structure{

struct Configuration{
  //---------------------------

  k4n::str::depth::Configuration depth;
  k4n::str::color::Configuration color;
  k4n::camera::Configuration camera;
  k4n::str::infra::Configuration ir;
  k4n::synchro::Configuration synchro;

  //---------------------------
};

}
