#pragma once

#include <k4a/k4a.hpp>


namespace k4n::str::camera{

struct Exposure{
  //---------------------------

  int32_t value = 15625;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_EXPOSURE_TIME_ABSOLUTE;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_AUTO;

  //---------------------------
};
struct White_balance{
  //---------------------------

  int32_t value = 4500;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_WHITEBALANCE;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_AUTO;

  //---------------------------
};
struct Brightness{
  //---------------------------

  int32_t value = 128;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_BRIGHTNESS;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Contrast{
  //---------------------------

  int32_t value = 5;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_CONTRAST;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Saturation{
  //---------------------------

  int32_t value = 32;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_SATURATION;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Sharpness{
  //---------------------------

  int32_t value = 2;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_SHARPNESS;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Backlight_compensation{
  //---------------------------

  bool value = 0;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_BACKLIGHT_COMPENSATION;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Gain{
  //---------------------------

  int32_t value = 0;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_GAIN;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Power_frequency{
  //---------------------------

  int32_t value = 2;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_POWERLINE_FREQUENCY;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};

}
