#pragma once

#include <memory>
#include <string>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::playback{class Sensor;}


namespace k4n::playback{

class Playback
{
public:
  //Constructor / Destructor
  Playback(k4n::Node* node_k4n);
  ~Playback();

public:
  //Main function
  void init_info(k4n::playback::Sensor& sensor);
  void init_playback(k4n::playback::Sensor& sensor);
  void find_timestamp(k4n::playback::Sensor& sensor);
  void close_playback(k4n::playback::Sensor& sensor);

  //Subfunction
  float find_mkv_ts_beg(std::string path);
  float find_mkv_ts_end(std::string path);

private:
  k4n::Structure* k4n_struct;
};

}
