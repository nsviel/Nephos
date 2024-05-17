#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model{class Model;}
namespace rad::model{class Measure;}
namespace utl::implot{class Plot;}


namespace rad::gui{

class Calibration
{
public:
  //Constructor / Destructor
  Calibration(rad::Node* node_radio);
  ~Calibration();

public:
  //Main function
  void draw_tab();

private:

};

}
