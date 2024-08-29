#pragma once

#include <Kinect/src/Structure/Data/Data.h>
#include <Utility/Namespace.h>
#include <k4a/k4a.hpp>
#include <string>

namespace k4n::structure{struct Data;}
namespace utl::media{struct Image;}


namespace k4n::color{

enum Resolution{
  OFF = 0,
  P720 = 1,
  P1080 = 2,
  P1440 = 3,
  P1536 = 4,
  P2160 = 5,
  P3072 = 6,
};

enum Format{
  MJPG = 0,
  NV12 = 1,
  YUY2 = 2,
  BGRA32 = 3,
  DEPTH16 = 4,
  IR16 = 5,
  CUSTOM = 6,
};

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

struct Configuration{
  //---------------------------

  //General
  bool enabled = true;

  std::string format_str = "";
  std::string resolution_str = "";

  k4a_image_format_t format = K4A_IMAGE_FORMAT_COLOR_YUY2;
  k4a_color_resolution_t resolution = K4A_COLOR_RESOLUTION_720P;

  //Control
  k4n::color::Exposure exposure;
  k4n::color::White_balance white_balance;
  k4n::color::Brightness brightness;
  k4n::color::Contrast contrast;
  k4n::color::Saturation saturation;
  k4n::color::Sharpness sharpness;
  k4n::color::Gain gain;
  k4n::color::Backlight_compensation backlight_compensation;
  k4n::color::Power_frequency power_frequency;

  //---------------------------
};

struct Structure{
  //Structure for sensor color field
  //---------------------------

  k4n::color::Configuration config;
  k4n::structure::Data data;
  utl::media::Image image;

  //---------------------------
};

}
