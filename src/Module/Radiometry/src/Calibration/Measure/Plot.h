#pragma once

#include <Utility/Specific/Common.h>

namespace rad::model{class Node;}
namespace rad::model{class Structure;}
namespace rad::calibration{class Model;}


namespace rad::calibration{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::model::Node* node_model);
  ~Plot();

public:
  //Main function
  void init();
  void plot_measure();

  //Subfunction
  void update_plot_data();
  void reset_plot_data();

private:

};

}
