#pragma once

#include <Utility/Specific/Common.h>

namespace rad::correction{class Node;}
namespace rad::correction{class Structure;}
namespace rad::correction{class Model;}


namespace rad::correction{

class Plot
{
public:
  //Constructor / Destructor
  Plot(rad::correction::Node* node_correction);
  ~Plot();

public:
  //Main function
  void init();
  void plot_measure();
  void plot_model();

  //Subfunction
  void update_plot_data();
  void reset_plot_data();

private:
  rad::correction::Structure* rad_struct;
  rad::correction::Model* rad_model;
};

}
