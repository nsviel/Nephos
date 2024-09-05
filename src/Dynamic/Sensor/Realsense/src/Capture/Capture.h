#pragma once

#include <librealsense2/rs.hpp>

namespace rlx{class Node;}
namespace rlx{class Structure;}


namespace rlx{

class Capture
{
public:
  //Constructor / Destructor
  Capture(rlx::Node* node_realsense);
  ~Capture();

public:
  //Main function
  void init();
  void capture();
  void display(rs2::frameset frames);
  int get_nb_device();

private:
  rlx::Structure* rlx_struct;
};

}
