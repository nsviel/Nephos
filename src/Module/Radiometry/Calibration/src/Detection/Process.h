#pragma once

namespace rad::calibration{class Node;}
namespace rad::calibration{class Structure;}
namespace rad::calibration{class Detection;}
namespace dat::gph{class Selection;}


namespace rad::calibration{

class Process
{
public:
  //Constructor / Destructor
  Process(rad::calibration::Node* node_detection);
  ~Process();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void step_detection();
  void step_measure();

private:
  rad::calibration::Structure* rad_struct;
  rad::calibration::Detection* rad_detection;
  dat::gph::Selection* dat_selection;
};

}
