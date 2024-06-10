#pragma once

#include <Radiometry/src/Detection/Sphere/Structure.h>
#include <Radiometry/src/Detection/Chart/Structure.h>


namespace rad::detection{

struct Structure{
  //---------------------------

  utl::media::Image image;
  rad::detection::sphere::Structure sphere;
  rad::detection::chart::Structure chart;

  //---------------------------
};

}
