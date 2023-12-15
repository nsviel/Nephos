#pragma once

#include <string>


namespace eng::kinect::structure{

struct Recorder{
  //---------------------------

  std::string path_to_save = "(not defined)";
  std::string folder_to_save = "(not defined)";

  float time_recording = 0;
  bool is_recording = false;

  //---------------------------
};

}
