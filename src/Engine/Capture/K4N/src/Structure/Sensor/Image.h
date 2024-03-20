#pragma once

#include <Utility/Namespace.h>

#include <string>
#include <mutex>


namespace k4n::structure{

struct Image{
  //Extracted sensor field images
  //---------------------------

  utl::media::Image color;
  utl::media::Image depth;
  utl::media::Image ir;
  utl::media::Image hough;

  //---------------------------
};

}
