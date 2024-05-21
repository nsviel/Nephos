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
  Measure(rad::Node* node_radio);
  ~Measure();

public:
  //Main function
  void init();

  //Subfunction
  void import_measure();
  void export_measure();
  void clear_measure();
  void find_measure_bound();

private:
  rad::Structure* rad_struct;
  rad::model::Plot* rad_plot;
};

}
