#pragma once

#include <Utility/Specific/common.h>
#include <k4arecord/playback.hpp>

namespace k4n::dev{class Sensor;}
namespace eng::ope{class Heatmap;}


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

  //Colorization function
  void make_colorization(k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba);
  void colorization_intensity(k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba);
  void colorization_heatmap(k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba);
  void colorization_structure(k4n::dev::Sensor* sensor, vector<vec4>& vec_rgba);

private:
  eng::ope::Heatmap* ope_heatmap;
};

}
