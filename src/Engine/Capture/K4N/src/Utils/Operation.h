#pragma once

#include <Utility/Specific/common.h>
#include <k4arecord/playback.hpp>

namespace k4n::dev{class Sensor;}


namespace k4n::utils{

class Operation
{
public:
  //Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Main function
  float find_mkv_ts_beg(string path);
  float find_mkv_ts_end(string path);

private:
};

}
