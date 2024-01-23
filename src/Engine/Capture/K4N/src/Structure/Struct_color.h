#pragma once

#include <k4a/k4a.hpp>
#include <string>

namespace k4n::src::str{

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

  std::string format_str;
  std::string resolution_str;
  std::string firmware_version;

  //Control
  k4n::src::str::Exposure exposure;
  k4n::src::str::White_balance white_balance;
  k4n::src::str::Brightness brightness;
  k4n::src::str::Contrast contrast;
  k4n::src::str::Saturation saturation;
  k4n::src::str::Sharpness sharpness;
  k4n::src::str::Gain gain;
  k4n::src::str::Backlight_compensation backlight_compensation;
  k4n::src::str::Power_frequency power_frequency;

  //---------------------------
};

struct Color{
  //---------------------------

  k4n::src::str::Color_config config;
  k4n::src::str::Image image;
  k4n::src::str::Image image_depth;

  //---------------------------
};

}
