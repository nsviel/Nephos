#pragma once

#include <Kinect/src/Structure/Transformation.h>
#include <Kinect/src/Structure/Configuration.h>
#include <Kinect/src/Structure/FPS.h>


namespace k4n{

struct Structure{
  //---------------------------

  k4n::transformation::Structure transformation;
  k4n::structure::Configuration config;
  k4n::structure::FPS fps;

  //---------------------------
};

}
