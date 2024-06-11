#pragma once

#include <Utility/Specific/Common.h>

namespace rad::model{class Node;}
namespace rad::model{class Structure;}
namespace rad::model::sphere{class Plot;}


namespace rad::model::sphere{

class Measure
{
public:
  //Constructor / Destructor
  Measure(rad::model::Node* node_model);
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
  rad::model::Structure* rad_struct;
  rad::model::sphere::Plot* rad_plot;
};

}
