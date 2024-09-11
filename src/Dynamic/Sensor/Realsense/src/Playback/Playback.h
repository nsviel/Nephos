#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::playback{class Configuration;}
namespace rlx::playback{class Sensor;}
namespace dat::base{class Sensor;}
namespace dat::elm{class Sensor;}


namespace rlx::playback{

class Playback
{
public:
  //Constructor / Destructor
  Playback(rlx::Node* node_realsense);
  ~Playback();

public:
  //Main function
  void init(rlx::playback::Sensor& sensor);
  void capture(dat::base::Sensor& sensor);
  void clean(rlx::playback::Sensor& sensor);

  //Subfunction
  void init_info(rlx::playback::Sensor& sensor);
  void init_capture(rlx::playback::Sensor& sensor);

private:
  rlx::Structure* rlx_struct;
  rlx::playback::Configuration* rlx_configuration;
  dat::elm::Sensor* dat_sensor;
};

}
