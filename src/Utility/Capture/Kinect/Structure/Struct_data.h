#pragma once

#include <Utility/Capture/Kinect/Structure/Namespace.h>
#include <string>


namespace util::kinect::structure{

struct Data{
  //---------------------------

  util::kinect::structure::Image color;
  util::kinect::structure::Image depth;
  util::kinect::structure::Image ir;

  //---------------------------
};

}
