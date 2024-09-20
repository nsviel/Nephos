#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::capture{class Configuration;}
namespace rlx::capture{class Sensor;}
namespace dat::base{class Sensor;}
namespace dat::elm{class Sensor;}
namespace dat::img{class Image;}


namespace rlx::capture{

class Capture
{
public:
  //Constructor / Destructor
  Capture(rlx::Node* node_realsense);
  ~Capture();

public:
  //Main function
  void init(rlx::capture::Sensor& sensor);
  void capture(dat::base::Sensor& sensor);
  void clean(rlx::capture::Sensor& sensor);

  //Subfunction
  void init_info(rlx::capture::Sensor& sensor);
  void init_image(rlx::capture::Sensor& sensor);
  void init_capture(rlx::capture::Sensor& sensor);

private:
  rlx::Structure* rlx_struct;
  rlx::capture::Configuration* rlx_configuration;
  dat::elm::Sensor* dat_sensor;
  dat::img::Image* dat_image;
};

}
