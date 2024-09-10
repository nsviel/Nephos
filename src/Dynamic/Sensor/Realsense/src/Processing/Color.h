#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::base{class Sensor;}


namespace rlx::processing{

class Color
{
public:
  //Constructor / Destructor
  Color(rlx::Node* node_realsense);
  ~Color();

public:
  //Main function
  void manage_color(rlx::base::Sensor& sensor);

private:
  rlx::Structure* rlx_struct;
};

}
