#pragma once

#include <Utility/Namespace.h>

#include <string>
#include <mutex>


namespace eng::k4n::structure{

struct Image{
  //---------------------------

  utl::media::Image color;
  utl::media::Image depth;
  utl::media::Image ir;

  std::mutex mutex;

  //---------------------------
};

}
