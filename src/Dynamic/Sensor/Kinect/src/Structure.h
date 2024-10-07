#pragma once

#include <Kinect/src/Structure/Configuration/Transformation.h>
#include <Kinect/src/Structure/Configuration/Configuration.h>
#include <Kinect/src/Structure/Configuration/FPS.h>
#include <Kinect/src/Structure/Device/Connection.h>
#include <Utility/Namespace.h>


namespace k4n{

struct Structure{
  //---------------------------

  k4n::transformation::Structure transformation;
  k4n::structure::Configuration config;
  k4n::structure::FPS fps;
  k4n::device::Connection connection;

  //---------------------------
};

}
