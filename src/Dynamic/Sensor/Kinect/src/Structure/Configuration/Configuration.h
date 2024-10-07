#pragma once

#include <Kinect/src/Structure/Configuration/FPS.h>
#include <Kinect/src/Structure/Configuration/Synchro.h>
#include <Kinect/src/Structure/Color/Configuration.h>
#include <Kinect/src/Structure/Data/Depth.h>
#include <Kinect/src/Structure/Data/Infrared.h>
#include <Kinect/src/Structure/Configuration/Camera.h>


namespace k4n::structure{

struct Configuration{
  //---------------------------

  k4n::depth::Configuration depth;
  k4n::str::color::Configuration color;
  k4n::camera::Configuration camera;
  k4n::infrared::Configuration ir;
  k4n::synchro::Configuration synchro;

  //---------------------------
};

}
