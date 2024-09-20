#pragma once

#include <memory>
#include <string>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::playback{class Sensor;}
namespace k4n::playback{class Configuration;}
namespace dat::elm{class Sensor;}
namespace dat::base{class Sensor;}
namespace dat::img{class Image;}


namespace k4n::playback{

class Playback
{
public:
  //Constructor / Destructor
  Playback(k4n::Node* node_k4n);
  ~Playback();

public:
  //Main function
  void init(k4n::playback::Sensor& sensor);
  void clean(k4n::playback::Sensor& sensor);

  //Subfunction
  void init_info(k4n::playback::Sensor& sensor);
  void init_playback(k4n::playback::Sensor& sensor);
  void init_timestamp(k4n::playback::Sensor& sensor);
  void init_image(k4n::playback::Sensor& sensor);
  void close_playback(k4n::playback::Sensor& sensor);
  void manage_capture(dat::base::Sensor& sensor);
  void manage_query(dat::base::Sensor& sensor, float value);

private:
  k4n::Structure* k4n_struct;
  k4n::playback::Configuration* k4n_config;
  dat::elm::Sensor* dat_sensor;
  dat::img::Image* dat_image;
};

}
