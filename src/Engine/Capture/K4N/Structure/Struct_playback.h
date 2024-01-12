#pragma once

#include <string>


namespace k4n::structure{

struct Config_int{
  //---------------------------

  std::string name;
  int value;

  //---------------------------
};

struct Playback{
  //---------------------------

  //File info
  std::string path;
  std::string filename;

  //Configuration info
  //Virer tous ca et mettre dans les bonnes structures
  std::string fps_str;
  std::string wired_sync_mode_str;
  std::string device_serial_number;

  //Stream info
  bool is_color;
  bool is_depth;
  bool is_infrared;
  bool is_imu;

  //---------------------------
};

}
