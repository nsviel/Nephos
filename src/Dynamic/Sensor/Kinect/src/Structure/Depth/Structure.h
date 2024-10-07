#pragma once

#include <Kinect/src/Structure/Depth/Configuration.h>
#include <Kinect/src/Structure/Depth/Data.h>
#include <Kinect/src/Structure/Depth/Texture.h>


namespace k4n::str::depth{

struct Structure{
  //---------------------------

  k4n::str::depth::Configuration config;
  k4n::str::depth::Data data;
  k4n::str::depth::Texture texture;

  //---------------------------
};

}
