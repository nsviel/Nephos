#pragma once

#include <Realsense/src/Structure/Buffer.h>
#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::base{class Sensor;}
namespace dat::base{class Sensor;}


namespace rlx::processing{

class Cloud
{
public:
  //Constructor / Destructor
  Cloud(rlx::Node* node_realsense);
  ~Cloud();

public:
  //Main function
  void extract_data(dat::base::Sensor& sensor);

  //Subfunction
  void extraction_init(rlx::base::Sensor& sensor);
  void extraction_xyz(rlx::base::Sensor& sensor, int& i);
  void extraction_transfer(rlx::base::Sensor& sensor);

private:
  rlx::Structure* rlx_struct;

  rlx::base::Buffer buffer;
};

}
