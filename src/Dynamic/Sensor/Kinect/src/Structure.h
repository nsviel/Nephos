#pragma once

#include <Kinect/src/Structure/Configuration/Transformation.h>
#include <Kinect/src/Structure/Configuration/Structure.h>
#include <Kinect/src/Structure/Configuration/FPS.h>
#include <Kinect/src/Structure/Device/Connection.h>
#include <Utility/Namespace.h>


namespace k4n{

struct Structure{
  //---------------------------

  k4n::transformation::Structure transformation;
  k4n::str::config::Structure config;
  k4n::device::Connection connection;

  //---------------------------
};

}
