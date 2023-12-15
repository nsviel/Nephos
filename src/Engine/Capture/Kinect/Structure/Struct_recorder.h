#pragma once

#include <string>


namespace eng::kinect::structure{

struct Recorder{
  //---------------------------

  std::string path_to_save = "";
  std::string folder_to_save = "";

  float time_recording = 0;
  bool is_recording = false;

  //---------------------------
};

}
