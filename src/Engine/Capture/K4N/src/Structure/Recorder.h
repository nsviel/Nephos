#pragma once

#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>
#include <string>


namespace k4n::recorder{

enum Mode{
  MKV = 0,
  PLY = 1,
};

}

namespace k4n::structure{

struct Recorder{
  //---------------------------

  std::string folder = "../media/record/ply";
  std::string filename = "capture";
  std::string path = "";

  int mode = k4n::recorder::PLY;
  double file_size = 0;
  float ts_rec = 0;
  float ts_beg;
  k4a::record handle;

  //---------------------------
};

}
