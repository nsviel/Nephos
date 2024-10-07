#pragma once

#include <Kinect/src/Structure/Infrared/Configuration.h>
#include <Kinect/src/Structure/Infrared/Data.h>
#include <Kinect/src/Structure/Infrared/Texture.h>


namespace k4n::str::infra{

struct Structure{
  //---------------------------

  k4n::str::infra::Configuration config;
  k4n::str::infra::Data data;
  k4n::str::infra::Texture texture;

  //---------------------------
};

}
