#pragma once

#include <Engine/Capture/K4N/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4N/Device/K4A_device.h>
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
  void make_colorization(k4n::structure::Cloud* cloud, vector<vec4>& vec_rgba);
  void colorization_intensity(k4n::structure::Cloud* cloud, vector<vec4>& vec_rgba);
  void colorization_heatmap(k4n::structure::Cloud* cloud, vector<vec4>& vec_rgba);

private:
  eng::ope::Heatmap* ope_heatmap;
};

}
