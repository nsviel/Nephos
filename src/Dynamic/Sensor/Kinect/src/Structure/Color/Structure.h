#pragma once

#include <Kinect/src/Structure/Color/Configuration.h>
#include <Kinect/src/Structure/Color/Data.h>
#include <Kinect/src/Structure/Color/Texture.h>


namespace k4n::str::color{

struct Structure{
  //---------------------------

  k4n::str::color::Configuration config;
  k4n::str::color::Data data;
  k4n::str::color::Texture texture;

  //---------------------------
};

}
