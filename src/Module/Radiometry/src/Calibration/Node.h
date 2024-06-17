#pragma once

#include <Radiometry/src/Calibration/Structure.h>
#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::calibration{class Structure;}


namespace rad::calibration{

class Node
{
public:
  //Constructor / Destructor
  Node(rad::Node* node_radio);
  ~Node();

public:
  //Main function

  inline rad::Node* get_node_radio(){return node_radio;}
  inline rad::calibration::Structure* get_rad_struct(){return rad_struct;}

private:
  rad::Node* node_radio;
  rad::calibration::Structure* rad_struct;
};

}
