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

  int tex_color_UID = 0;
  int tex_depth_UID = 0;
  int tex_ir_UID = 0;
  
  std::mutex mutex;

  //---------------------------
};

}
