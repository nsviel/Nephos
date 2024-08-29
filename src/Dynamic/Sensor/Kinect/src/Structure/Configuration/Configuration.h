#pragma once

#include <Kinect/src/Structure/FPS.h>
#include <Kinect/src/Structure/Color.h>
#include <Kinect/src/Structure/Depth.h>
#include <Kinect/src/Structure/Infrared.h>
#include <Kinect/src/Structure/Synchro.h>
#include <k4a/k4a.hpp>
#include <string>


namespace k4n::structure{

struct Configuration{
  //---------------------------

  k4n::depth::Configuration depth;
  k4n::color::Configuration color;
  k4n::infrared::Configuration ir;
  k4n::synchro::Configuration synchro;

  //---------------------------
};

}
