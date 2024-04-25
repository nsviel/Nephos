#pragma once

#include <Utility/Specific/Common.h>
#include <k4arecord/playback.hpp>

namespace k4n::dev{class Sensor;}
namespace k4n::dev{class Master;}


namespace k4n::utils{

class Operation
{
public:
  //Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Data operation
  void make_normal_from_depth_image(k4n::dev::Sensor* sensor);

  //Player operation
  float find_mkv_ts_beg(string path);
  float find_mkv_ts_end(string path);

private:
};

}
