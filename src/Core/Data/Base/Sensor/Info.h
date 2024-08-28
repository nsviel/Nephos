#pragma once

#include <Data/Base/Sensor/Recorder.h>
#include <vector>
#include <string>


namespace dat::base::sensor{

struct Info{
  //---------------------------

  std::string model = "";
  std::string serial_number = "";
  std::string depth_mode = "";
  std::vector<uint16_t> buffer_depth;
  std::vector<uint16_t> buffer_ir;
  std::vector<std::string> vec_depth_mode;
  std::vector<dat::base::sensor::Recorder*> vec_recorder;

  //---------------------------
};

}
