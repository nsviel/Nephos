#pragma once

#include <Engine/Capture/K4A/Structure/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Capture/K4A/Device/K4A_device.h>
#include <Engine/Operation/Color/Heatmap.h>
#include <k4arecord/playback.hpp>


namespace k4a::utils{

class Operation
{
public:
  //Constructor / Destructor
  Operation();
  ~Operation();

public:
  //Main function
  void make_colorization(k4a::stucture::Cloud* cloud, vector<vec4>& vec_rgba);
  void colorization_intensity(k4a::stucture::Cloud* cloud, vector<vec4>& vec_rgba);
  void colorization_heatmap(k4a::stucture::Cloud* cloud, vector<vec4>& vec_rgba);

private:
  eng::ope::Heatmap* ope_heatmap;
};

}
