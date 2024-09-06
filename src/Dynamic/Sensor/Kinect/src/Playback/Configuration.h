#pragma once

#include <memory>
#include <string>

namespace k4n{class Node;}
namespace k4n::playback{class Sensor;}


namespace k4n::playback{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(k4n::Node* node_k4n);
  ~Configuration();

public:
  //Main function
  void init_configuration(k4n::playback::Sensor& sensor);
  void find_configuration(k4n::playback::Sensor& sensor);
  void find_calibration(k4n::playback::Sensor& sensor);

  //Subfunction
  std::string find_mode_fps(int mode);
  std::string find_mode_synchro(int mode);
  std::string find_mode_depth(int mode);
  std::string find_resolution_depth(int mode);
  std::string find_mode_color_resolution(int mode);
  std::string find_mode_color_format(int mode);
  float find_mkv_ts_beg(std::string path);
  float find_mkv_ts_end(std::string path);

private:
};

}
