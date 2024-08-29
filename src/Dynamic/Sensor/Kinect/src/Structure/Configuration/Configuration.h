#pragma once

#include <Kinect/src/Structure/Configuration/FPS.h>
#include <Kinect/src/Structure/Configuration/Synchro.h>
#include <Kinect/src/Structure/Data/Color.h>
#include <Kinect/src/Structure/Data/Depth.h>
#include <Kinect/src/Structure/Data/Infrared.h>


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
