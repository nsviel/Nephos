#pragma once

#include <k4a/k4a.hpp>
#include <string>

namespace k4n::structure{

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

struct Color_config{
  //---------------------------

  //General
  bool enabled = true;
  k4a_image_format_t format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  k4a_color_resolution_t resolution = K4A_COLOR_RESOLUTION_720P;

  //Control
  k4n::structure::Exposure exposure;
  k4n::structure::White_balance white_balance;
  k4n::structure::Brightness brightness;
  k4n::structure::Contrast contrast;
  k4n::structure::Saturation saturation;
  k4n::structure::Sharpness sharpness;
  k4n::structure::Gain gain;
  k4n::structure::Backlight_compensation backlight_compensation;
  k4n::structure::Power_frequency power_frequency;

  //---------------------------
};

struct Color{
  //---------------------------

  k4n::structure::Color_config config;
  k4n::structure::Image image;
  k4n::structure::Image image_depth;

  //---------------------------
};

}
