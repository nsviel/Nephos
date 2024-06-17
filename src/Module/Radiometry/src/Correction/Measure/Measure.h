#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Plot;}


namespace rad::correction{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::correction::Node* node_correction);
  ~Measure();

public:
  //Main function
  void import_measure();
  void export_measure();
  void clear_measure();

  //Subfunction
  void init();
  void find_optimization_bound();

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Plot* rad_plot;
};

}
