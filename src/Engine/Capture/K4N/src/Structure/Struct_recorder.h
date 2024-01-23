#pragma once

#include <k4a/k4a.hpp>
#include <k4arecord/record.hpp>
#include <string>


namespace k4n::src::str{

struct Recorder{
  //---------------------------

  std::string path = "(not defined)";
  std::string folder = "(not defined)";
  std::string format = ".mkv";

  float ts_rec = 0;
  float ts_beg;
  k4a::record recorder;

  //---------------------------
};

}
