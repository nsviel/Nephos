#pragma once

#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>
#include <string>


namespace k4n::structure{

struct Recorder{
  //---------------------------

  std::string path = "";
  std::string folder = "";
  std::string format = ".mkv";

  float ts_rec = 0;
  float ts_beg;
  k4a::record recorder;

  //---------------------------
};

}
