#pragma once

#include <Kinect/src/Structure/Data/Depth/Cloud.h>
#include <Kinect/src/Structure/Data/Depth/Configuration.h>
#include <Kinect/src/Structure/Data/Depth/Data.h>
#include <Kinect/src/Structure/Data/Depth/Texture.h>


namespace k4n::str::depth{

struct Structure{
  //---------------------------

  k4n::str::depth::Cloud cloud;
  k4n::str::depth::Configuration config;
  k4n::str::depth::Data data;
  k4n::str::depth::Texture texture;

  //---------------------------
};

}
