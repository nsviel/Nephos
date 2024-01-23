#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/src/Device/Namespace.h>
#include <Engine/Capture/K4N/src/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Operation/Color/Heatmap.h>
#include <k4arecord/playback.hpp>


namespace k4n::src::utils{

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
  void make_colorization(k4n::src::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba);
  void colorization_intensity(k4n::src::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba);
  void colorization_heatmap(k4n::src::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba);

private:
  eng::ope::Heatmap* ope_heatmap;
};

}
