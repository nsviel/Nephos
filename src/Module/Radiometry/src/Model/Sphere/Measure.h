#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad{class Structure;}
namespace rad::model{class Plot;}


namespace rad::model{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::Node* node_radio, rad::model::Plot* rad_plot);
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
  rad::Structure* rad_struct;
  rad::model::Plot* rad_plot;
};

}
