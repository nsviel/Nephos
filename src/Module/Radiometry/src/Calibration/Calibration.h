#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}


namespace rad{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(rad::Node* node_radio);
  ~Calibration();

public:
  //Main function

private:
  rad::Structure* rad_struct;
};

}
