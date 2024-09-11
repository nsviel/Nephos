#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::capture{class Sensor;}
namespace dat::base{class Sensor;}


namespace rlx::playback{

class Configuration
{
public:
  //Constructor / Destructor
  Configuration(rlx::Node* node_realsense);
  ~Configuration();

public:
  //Main function
  void init(rlx::capture::Sensor& sensor);

private:
  rlx::Structure* rlx_struct;
};

}
