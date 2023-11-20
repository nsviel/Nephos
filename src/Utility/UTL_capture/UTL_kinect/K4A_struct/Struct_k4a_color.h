#ifndef STRUCT_K4A_COLOR_H
#define STRUCT_K4A_COLOR_H

#include <k4a/k4a.hpp>
#include <string>


struct Struct_k4a_color{
  //---------------------------

  int32_t exposure_time_us;
  int32_t white_balance;
  int32_t brightness;
  int32_t contrast;
  int32_t saturation;
  int32_t sharpness;
  int32_t backlight_compensation;
  int32_t gain;
  int32_t powerline_frequency;

  k4a_color_control_mode_t mode_manuel = K4A_COLOR_CONTROL_MODE_MANUAL;
  k4a_color_control_mode_t mode_auto = K4A_COLOR_CONTROL_MODE_AUTO;
  k4a_color_control_command_t command_exposure = K4A_COLOR_CONTROL_EXPOSURE_TIME_ABSOLUTE;
  k4a_color_control_command_t command_white_balance = K4A_COLOR_CONTROL_WHITEBALANCE;
  k4a_color_control_command_t command_brigthneww = K4A_COLOR_CONTROL_BRIGHTNESS;
  k4a_color_control_command_t command_contrast = K4A_COLOR_CONTROL_CONTRAST;
  k4a_color_control_command_t command_saturation = K4A_COLOR_CONTROL_SATURATION;
  k4a_color_control_command_t command_sharpness = K4A_COLOR_CONTROL_SHARPNESS;
  k4a_color_control_command_t command_backlight_compensation = K4A_COLOR_CONTROL_BACKLIGHT_COMPENSATION;
  k4a_color_control_command_t command_gain = K4A_COLOR_CONTROL_GAIN;
  k4a_color_control_command_t command_powerline_frequency = K4A_COLOR_CONTROL_POWERLINE_FREQUENCY;

  //---------------------------
};



#endif
