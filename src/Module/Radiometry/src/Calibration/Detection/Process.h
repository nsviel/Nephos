#pragma once

#include <Utility/Specific/Common.h>

namespace rad::detection{class Node;}
namespace rad::detection{class Structure;}
namespace rad::calibration{class Detection;}
namespace dat{class Selection;}


namespace rad::calibration{

class Process
{
public:
  //Constructor / Destructor
  Process(rad::detection::Node* node_detection);
  ~Process();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void step_detection();

private:
  rad::detection::Structure* rad_struct;
  rad::calibration::Detection* chart_detection;
  dat::Selection* dat_selection;
};

}
