#ifndef STRUCT_K4A_COLOR_H
#define STRUCT_K4A_COLOR_H

#include <k4a/k4a.hpp>
#include <string>


struct Exposure{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_EXPOSURE_TIME_ABSOLUTE;

  //---------------------------
};
struct White_balance{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_WHITEBALANCE;

  //---------------------------
};
struct Brightness{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_BRIGHTNESS;

  //---------------------------
};
struct Contrast{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_CONTRAST;

  //---------------------------
};
struct Saturation{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_SATURATION;

  //---------------------------
};
struct Sharpness{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_SHARPNESS;

  //---------------------------
};
struct Backlight_compensation{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_BACKLIGHT_COMPENSATION;

  //---------------------------
};
struct Gain{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_GAIN;

  //---------------------------
};
struct Powerline_frequency{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_POWERLINE_FREQUENCY;

  //---------------------------
};

struct Struct_k4a_color{
  //---------------------------

  Exposure exposure;
  White_balance white_balance;
  Brightness brightness;
  Contrast contrast;
  Saturation saturation;
  Sharpness sharpness;
  Gain gain;
  Backlight_compensation backlight_compensation;
  Powerline_frequency powerline_frequency;

  k4a_color_control_mode_t mode_manuel = K4A_COLOR_CONTROL_MODE_MANUAL;
  k4a_color_control_mode_t mode_auto = K4A_COLOR_CONTROL_MODE_AUTO;

  //---------------------------
};



#endif
