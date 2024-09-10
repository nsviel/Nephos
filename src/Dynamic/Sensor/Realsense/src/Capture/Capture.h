#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}
namespace rlx::capture{class Sensor;}


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
  void capture();

  //Subfunction
  void init_info(rlx::capture::Sensor& sensor);
  void init_capture(rlx::capture::Sensor& sensor);
  void display(rs2::frameset frames);
  int get_nb_device();

private:
  rlx::Structure* rlx_struct;
};

}
