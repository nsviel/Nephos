#pragma once

#include <k4a/k4a.hpp>


namespace k4n::str::camera{

struct Structure{
  //---------------------------

  k4n::str::camera::Exposure exposure;
  k4n::str::camera::White_balance white_balance;
  k4n::str::camera::Brightness brightness;
  k4n::str::camera::Contrast contrast;
  k4n::str::camera::Saturation saturation;
  k4n::str::camera::Sharpness sharpness;
  k4n::str::camera::Gain gain;
  k4n::str::camera::Backlight_compensation backlight_compensation;
  k4n::str::camera::Power_frequency power_frequency;

  //---------------------------
};

}
