#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rnd{class Stream;}
namespace dyn::base{class Sensor;}


namespace rad::gui{

class Correction
{
public:
  //Constructor / Destructor
  Correction(rad::Node* node_radio);
  ~Correction();

public:
  //Main function
  void draw_tab(dyn::base::Sensor* sensor);

  //Subfunction
  void display_image();

private:
  rad::correction::Structure* rad_struct;
  rnd::Stream* stream;
};

}
