#pragma once

#include <k4a/k4a.hpp>
#include <string>

namespace util::kinect::structure{

struct Exposure{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_EXPOSURE_TIME_ABSOLUTE;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_AUTO;

  //---------------------------
};
struct White_balance{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_WHITEBALANCE;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_AUTO;

  //---------------------------
};
struct Brightness{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_BRIGHTNESS;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Contrast{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_CONTRAST;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Saturation{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_SATURATION;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Sharpness{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_SHARPNESS;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Backlight_compensation{
  //---------------------------

  bool value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_BACKLIGHT_COMPENSATION;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Gain{
  //---------------------------

  int32_t value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_GAIN;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};
struct Power_frequency{
  //---------------------------

  std::string value;
  k4a_color_control_command_t command = K4A_COLOR_CONTROL_POWERLINE_FREQUENCY;
  k4a_color_control_mode_t mode = K4A_COLOR_CONTROL_MODE_MANUAL;

  //---------------------------
};

struct Color{
  //---------------------------

  //General
  bool enabled = true;
  k4a_image_format_t format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  k4a_color_resolution_t resolution = K4A_COLOR_RESOLUTION_720P;

  //Control
  util::kinect::structure::Exposure exposure;
  util::kinect::structure::White_balance white_balance;
  util::kinect::structure::Brightness brightness;
  util::kinect::structure::Contrast contrast;
  util::kinect::structure::Saturation saturation;
  util::kinect::structure::Sharpness sharpness;
  util::kinect::structure::Gain gain;
  util::kinect::structure::Backlight_compensation backlight_compensation;
  util::kinect::structure::Power_frequency power_frequency;

  //---------------------------
};

}
