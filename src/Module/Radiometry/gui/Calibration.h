#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rnd{class Stream;}


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

  //Subfunction
  void display_image();

private:
  rad::Structure* rad_struct;
  rnd::Stream* stream;
};

}
