#pragma once

#include <Utility/Specific/Common.h>

namespace rad::calibration{class Node;}
namespace rad::calibration{class Structure;}
namespace rad::calibration{class Plot;}


namespace rad::calibration{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::calibration::Node* node_calibration);
  ~Measure();

public:
  //Main function
  void import_measure();
  void export_measure();
  void clear_measure();

  //Subfunction
  void init();

private:
  rad::calibration::Structure* rad_struct;
  rad::calibration::Plot* rad_plot;
};

}
