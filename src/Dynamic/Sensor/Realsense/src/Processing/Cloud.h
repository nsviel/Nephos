#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace dat::base{class Sensor;}
namespace utl::media{class Image;}


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
  
private:
  rlx::Structure* rlx_struct;
};

}
