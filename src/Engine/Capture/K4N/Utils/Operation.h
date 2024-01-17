#pragma once

#include <Engine/Capture/K4N/Namespace.h>
#include <Engine/Capture/K4N/Device/Namespace.h>
#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Operation/Color/Heatmap.h>
#include <k4arecord/playback.hpp>


namespace k4n::utils{

class Operation
{
public:
  //Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Main function
  void playback_find_duration(k4n::dev::Sensor* k4n_sensor);
  void make_colorization(k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba);
  void colorization_intensity(k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba);
  void colorization_heatmap(k4n::dev::Sensor* k4n_sensor, vector<vec4>& vec_rgba);

private:
  eng::ope::Heatmap* ope_heatmap;
};

}
