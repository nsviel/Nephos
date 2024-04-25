#pragma once

#include <Utility/Namespace.h>

namespace utl::media{struct Image;}


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
