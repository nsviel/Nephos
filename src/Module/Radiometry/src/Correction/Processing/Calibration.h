#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::correction{class Structure;}


namespace rad::correction{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(rad::Node* node_radio);
  ~Calibration();

public:
  //Main function

private:
  rad::correction::Structure* rad_struct;
};

}
