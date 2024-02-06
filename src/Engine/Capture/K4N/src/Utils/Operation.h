#pragma once

#include <Utility/Specific/common.h>
#include <k4arecord/playback.hpp>

namespace eng::k4n::dev{class Sensor;}
namespace eng::ope{class Heatmap;}


namespace eng::k4n::utils{

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
  void make_colorization(eng::k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba);
  void colorization_intensity(eng::k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba);
  void colorization_heatmap(eng::k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba);

private:
  eng::ope::Heatmap* ope_heatmap;
};

}
