#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::base{class Sensor;}


namespace rlx::processing{

class Depth
{
public:
  //Constructor / Destructor
  Depth(rlx::Node* node_realsense);
  ~Depth();

public:
  //Main function
  void manage_depth(rlx::base::Sensor& sensor);

private:
  rlx::Structure* rlx_struct;
};

}
